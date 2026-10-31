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

void LaunchVectorAdd(const float* a, const float* b, float* c,
                     std::size_t n, int threads, bool vectorized)
{
    if (n == 0) return;
    if (vectorized)
        LaunchVectorAddVectorized(a, b, c, n, threads);
    else
        VectorAddScalar<<<unsigned((n + threads - 1) / threads), threads>>>(a, b, c, n);
}

// Host-side setup stays outside the kernels so experiments only change GPU work.
struct Events {
    cudaEvent_t start{}, stop{};
    Events() {
        CheckCuda(cudaEventCreate(&start), "Create start event");
        try { CheckCuda(cudaEventCreate(&stop), "Create stop event"); }
        catch (...) { cudaEventDestroy(start); throw; }
    }
    ~Events() { cudaEventDestroy(start); cudaEventDestroy(stop); }
};

void Run(std::size_t n, int threads, int iterations, bool vectorized)
{
    std::vector<float> a(n), b(n), c(n);
    for (std::size_t i = 0; i < n; ++i) {
        a[i] = float(int(i % 17) - 8) * 0.25f;
        b[i] = float(int(i % 11) - 5) * 0.5f;
    }
    if (n == 0) { std::cout << "PASS: empty input (no launch)\n"; return; }
    DeviceBuffer da(n), db(n), dc(n);
    const auto bytes = n * sizeof(float);
    CheckCuda(cudaMemcpy(da.data(), a.data(), bytes, cudaMemcpyHostToDevice), "Copy A");
    CheckCuda(cudaMemcpy(db.data(), b.data(), bytes, cudaMemcpyHostToDevice), "Copy B");
    auto launch = [&] {
        LaunchVectorAdd(da.data(), db.data(), dc.data(), n, threads, vectorized);
        CheckCuda(cudaGetLastError(), "Launch vector add");
    };
    launch(); // One warmup; profiler commands skip this launch.
    CheckCuda(cudaDeviceSynchronize(), "Warmup");
    Events events;
    CheckCuda(cudaEventRecord(events.start), "Record start");
    for (int i = 0; i < iterations; ++i) launch();
    CheckCuda(cudaEventRecord(events.stop), "Record stop");
    CheckCuda(cudaEventSynchronize(events.stop), "Execute kernels");
    float ms = 0;
    CheckCuda(cudaEventElapsedTime(&ms, events.start, events.stop), "Elapsed time");
    CheckCuda(cudaMemcpy(c.data(), dc.data(), bytes, cudaMemcpyDeviceToHost), "Copy result");
    for (std::size_t i = 0; i < n; ++i)
        if (!std::isfinite(c[i]) || std::fabs(c[i] - (a[i] + b[i])) > 1e-5f)
            throw std::runtime_error("Mismatch at index " + std::to_string(i));
    const float average = ms / iterations;
    std::cout << "PASS: " << (vectorized ? "vectorized" : "scalar") << " n=" << n
              << " threads=" << threads << " average=" << average << " ms"
              << " effective=" << (3.0 * bytes / (average * 1e6)) << " GB/s\n";
}

