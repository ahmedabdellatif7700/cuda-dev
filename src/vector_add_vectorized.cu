#include <cuda_runtime.h>
#include <cstddef>

// Compare with the scalar kernel: each thread handles four adjacent floats.
// cudaMalloc provides alignment for float4; don't pass offset device pointers.
__global__ void VectorAddFloat4(const float* a, const float* b, float* c, std::size_t n)
{
    const std::size_t i = std::size_t(blockIdx.x) * blockDim.x + threadIdx.x;
    const std::size_t vectors = n / 4;
    if (i < vectors)
    {
        const float4 x = reinterpret_cast<const float4*>(a)[i];
        const float4 y = reinterpret_cast<const float4*>(b)[i];
        reinterpret_cast<float4*>(c)[i] = make_float4(x.x + y.x, x.y + y.y,
                                                   x.z + y.z, x.w + y.w);
    }
    // Up to three remaining elements, handled by the first few threads.
    const std::size_t tail = vectors * 4 + i;
    if (i < n % 4)
        c[tail] = a[tail] + b[tail];
}

void LaunchVectorAddVectorized(const float* a, const float* b, float* c,
                              std::size_t n, int threads)
{
    const std::size_t work = (n + 3) / 4;
    VectorAddFloat4<<<unsigned((work + threads - 1) / threads), threads>>>(a, b, c, n);
}
