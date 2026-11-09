#include "CudaSupport.h"
#include "SharedReduce.h"

__global__ void SharedReduceKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd5];  // Read global data.
    // bar.sync 0;  // Block-wide barrier.
    // add.f32 %f4, %f3, %f2;  // Add float values.
    extern __shared__ float values[];
    const int lane = threadIdx.x;
    values[lane] = input[lane];
    __syncthreads();
    for (int stride = 128; stride > 0; stride /= 2)
    {
        if (lane < stride) values[lane] += values[lane + stride];
        __syncthreads();
    }
    if (lane == 0) output[0] = values[0];
}

void LaunchSharedReduce(const float* input, float* output, int count)
{
    SharedReduceKernel<<<1, 256, 256 * sizeof(float)>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch SharedReduce");
}
