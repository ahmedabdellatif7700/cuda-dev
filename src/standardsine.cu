#include "CudaSupport.h"
#include "StandardSine.h"

__global__ void StandardSineKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd14];  // Read global data.
    // mul.f32 %f14, %f1, 0f3F22F983;  // Multiply float values.
    // ld.global.nc.u32 %r28, [%rd29];  // Read global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count) output[index] = sinf(input[index]);
}

void LaunchStandardSine(const float* input, float* output, int count)
{
    StandardSineKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch StandardSine");
}
