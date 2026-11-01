#include "CudaSupport.h"
#include <cmath>
#include <iostream>
#include <vector>

// Start here: one thread computes one output element.
__global__ void VectorAddScalar(const float* a, const float* b, float* c, std::size_t n)
{
    const std::size_t i = std::size_t(blockIdx.x) * blockDim.x + threadIdx.x;
    if (i < n)
        c[i] = a[i] + b[i];
}

void LaunchVectorAddVectorized(const float*, const float*, float*, std::size_t, int);

namespace
{
void LaunchVectorAdd(const float* a, const float* b, float* c,
                     std::size_t n, int threads, bool vectorized)
{
    if (n == 0) return;
    if (vectorized)
        LaunchVectorAddVectorized(a, b, c, n, threads);
    else
        VectorAddScalar<<<unsigned((n + threads - 1) / threads), threads>>>(a, b, c, n);
}

// CUDA events measure elapsed GPU time. Destruction releases their resources.
struct Events {
    cudaEvent_t start{}, stop{};
    Events() {
        CheckCuda(cudaEventCreate(&start), "Create start event");
        try { CheckCuda(cudaEventCreate(&stop), "Create stop event"); }
        catch (...) { cudaEventDestroy(start); throw; }
    }
    ~Events() { cudaEventDestroy(start); cudaEventDestroy(stop); }
    Events(const Events&) = delete;
    Events& operator=(const Events&) = delete;
};

void Run(std::size_t n, int threads, int iterations, bool vectorized)
{
    // 1. Prepare input on the CPU. std::vector owns and releases host memory.
    std::vector<float> a(n), b(n), c(n);
    for (std::size_t i = 0; i < n; ++i) {
        a[i] = static_cast<float>(i % 17) * 0.25f;
        b[i] = static_cast<float>(i % 11) * -0.5f;
    }
    if (n == 0) { std::cout << "PASS: empty input (no launch)\n"; return; }
    // 2. Allocate GPU memory and copy the input to it.
    DeviceBuffer device_a(n), device_b(n), device_c(n);
    const auto bytes = n * sizeof(float);
    CheckCuda(cudaMemcpy(device_a.data(), a.data(), bytes, cudaMemcpyHostToDevice), "Copy A");
    CheckCuda(cudaMemcpy(device_b.data(), b.data(), bytes, cudaMemcpyHostToDevice), "Copy B");
    // 3. Warm up, then time repeated launches without including transfers.
    const auto launch = [&] {
        LaunchVectorAdd(device_a.data(), device_b.data(), device_c.data(), n, threads, vectorized);
        CheckCuda(cudaGetLastError(), "Launch vector add");
    };
    launch(); // One warmup before timed execution.
    CheckCuda(cudaDeviceSynchronize(), "Warmup");
    Events events;
    CheckCuda(cudaEventRecord(events.start), "Record start");
    for (int i = 0; i < iterations; ++i) launch();
    CheckCuda(cudaEventRecord(events.stop), "Record stop");
    CheckCuda(cudaEventSynchronize(events.stop), "Execute kernels");
    float ms = 0;
    CheckCuda(cudaEventElapsedTime(&ms, events.start, events.stop), "Elapsed time");
    // 4. Copy back and check every result against the CPU calculation.
    CheckCuda(cudaMemcpy(c.data(), device_c.data(), bytes, cudaMemcpyDeviceToHost), "Copy result");
    for (std::size_t i = 0; i < n; ++i)
        if (!std::isfinite(c[i]) || std::fabs(c[i] - (a[i] + b[i])) > 1e-5f)
            throw std::runtime_error("Mismatch at index " + std::to_string(i));
    const float average = ms / static_cast<float>(iterations);
    std::cout << "PASS: " << (vectorized ? "vectorized" : "scalar") << " n=" << n
              << " threads=" << threads << " average=" << average << " ms"
              << '\n';
}

} // namespace

void RunVectorAddExamples(std::size_t count, int threads, int repetitions)
{
    if (count > (1u << 24))
        throw std::invalid_argument("Use at most 2^24 elements for this example");
    if (threads < 1 || threads > 1024 || repetitions < 1)
        throw std::invalid_argument("Use 1..1024 threads and at least one repetition");

    Run(count, threads, repetitions, false); // One float per thread.
    Run(count, threads, repetitions, true);  // Four floats per thread.
}
