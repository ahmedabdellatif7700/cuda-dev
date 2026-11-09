#include "CudaSupport.h"
#include "StridedRead.h"

__global__ void StridedReadKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd5];  // Read global data.
    // st.global.f32 [%rd8], %f1;  // Write global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count / 4) output[index] = input[4 * index];
}

void LaunchStridedRead(const float* input, float* output, int count)
{
    StridedReadKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch StridedRead");
}
