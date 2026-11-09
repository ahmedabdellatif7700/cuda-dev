#include <cuda_runtime.h>
#include "ChildSum.cuh"
__global__ void ChildSum(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f29, [%rd5];  // Read global data.
    // bar.sync 0;  // Block-wide barrier.
    // add.f32 %f6, %f5, %f4;  // Add float values.
    __shared__ float values[256];
    const int lane = threadIdx.x;
    values[lane] = lane < count ? input[lane] : 0.0f;
    __syncthreads();
    for (int stride = 1; stride < 256; stride *= 2)
    {
        if (lane % (2 * stride) == 0) values[lane] += values[lane + stride];
        __syncthreads();
    }
    if (lane == 0) output[0] = values[0];
}
