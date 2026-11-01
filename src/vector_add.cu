#include "CudaSupport.h"
#include "VectorAdd.h"

// Each thread computes one independent output element.
__global__ void VectorAddScalar(const float* a, const float* b, float* c, std::size_t n)
{
    const auto i = std::size_t(blockIdx.x) * blockDim.x + threadIdx.x;
    if (i < n)
        c[i] = a[i] + b[i];
}

void LaunchVectorAddScalar(const float* a, const float* b, float* c,
                           std::size_t n, int threads)
{
    if (n == 0)
        return;
    const auto blocks = static_cast<unsigned>((n + threads - 1) / threads);
    VectorAddScalar<<<blocks, threads>>>(a, b, c, n);
    CheckCuda(cudaGetLastError(), "Launch VectorAddScalar");
}
