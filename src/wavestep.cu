#include "CudaSupport.h"
#include "WaveStep.h"

__global__ void WaveStepKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // st.global.u32 [%rd1], %r6;  // Write global data.
    // ld.global.f32 %f1, [%rd8+64];  // Read global data.
    // ld.global.f32 %f2, [%rd8];  // Read global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    const int row = index / 8, column = index % 8;
    if (index < 64)
    {
        output[index] = 0.0f;
        if (row > 0 && row < 7 && column > 0 && column < 7)
        {
            const float laplacian = input[index - 8] + input[index + 8]
                                  + input[index - 1] + input[index + 1] - 4.0f * input[index];
            // Initial previous state equals current state for this first step.
            output[index] = input[index] + 0.1f * laplacian;
        }
    }
}

void LaunchWaveStep(const float* input, float* output, int count)
{
    WaveStepKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch WaveStep");
}
