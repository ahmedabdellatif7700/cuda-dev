#include "CudaSupport.h"
#include "ConstantStencil.h"
__constant__ float coefficients[3];
__global__ void ConstantStencilKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f7, [%rd2];  // Read global data.
    // mul.f32 %f13, %f7, %f6;  // Multiply float values.
    // ld.global.f32 %f9, [%rd2+-4];  // Read global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count)
    {
        float value = input[index] * coefficients[1];
        if (index > 0) value += input[index - 1] * coefficients[0];
        if (index + 1 < count) value += input[index + 1] * coefficients[2];
        output[index] = value;
    }
}

void LaunchConstantStencil(const float* input, float* output, int count)
{
    const float weights[3] = {0.25f, 0.5f, 0.25f};
    CheckCuda(cudaMemcpyToSymbol(coefficients, weights, sizeof(weights)), "Upload coefficients");
    ConstantStencilKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch ConstantStencil");
}
