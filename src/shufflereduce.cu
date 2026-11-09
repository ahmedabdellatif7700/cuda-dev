#include "CudaSupport.h"
#include "ShuffleReduce.h"

__global__ void ShuffleReduceKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f2, [%rd5];  // Read global data.
    // shfl.sync.down.b32 %r7|%p1, %r2, %r5, %r4, %r6;  // Communicate between participating lanes.
    // add.f32 %f4, %f2, %f3;  // Add float values.
    const int lane = threadIdx.x;
    float value = input[lane];
    for (int offset = 16; offset > 0; offset /= 2)
        value += __shfl_down_sync(0xffffffffu, value, offset);
    if (lane == 0) output[0] = value;
}

void LaunchShuffleReduce(const float* input, float* output, int count)
{
    ShuffleReduceKernel<<<1, 32>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch ShuffleReduce");
}
