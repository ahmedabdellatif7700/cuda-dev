#include "CudaSupport.h"
#include "IntrinsicSine.h"

__global__ void IntrinsicSineKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd5];  // Read global data.
    // st.global.f32 [%rd7], %f2;  // Write global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count) output[index] = __sinf(input[index]);
}

void LaunchIntrinsicSine(const float* input, float* output, int count)
{
    IntrinsicSineKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch IntrinsicSine");
}
