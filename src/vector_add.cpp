#include "CudaSupport.h"
#include "VectorAdd.h"

void VectorAdd(std::span<const float> a, std::span<const float> b,
               std::span<float> c, int threads)
{
    if (a.size() != b.size() || a.size() != c.size())
        throw std::invalid_argument("Vector sizes must match");
    if (threads < 1 || threads > 1024 || a.size() > (1u << 24))
        throw std::invalid_argument("Use at most 2^24 elements and 1..1024 threads");
    if (a.empty())
        return;

    const auto n = a.size();
    const auto bytes = a.size_bytes();
    DeviceBuffer device_a(n), device_b(n), device_c(n);
    CheckCuda(cudaMemcpy(device_a.data(), a.data(), bytes, cudaMemcpyHostToDevice), "Copy A");
    CheckCuda(cudaMemcpy(device_b.data(), b.data(), bytes, cudaMemcpyHostToDevice), "Copy B");

    LaunchVectorAddScalar(device_a.data(), device_b.data(), device_c.data(), n, threads);
    // The blocking copy waits for the result and reports execution errors.
    CheckCuda(cudaMemcpy(c.data(), device_c.data(), bytes, cudaMemcpyDeviceToHost), "Copy result");
}
