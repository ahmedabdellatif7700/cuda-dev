#include "CudaSupport.h"
#include "BranchPaths.h"

__global__ void BranchPathsKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd6];  // Read global data.
    // st.global.f32 [%rd9], %f67;  // Write global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count)
    {
        float value = input[index];
        if (threadIdx.x % 2 == 0)
            for (int step = 0; step < 32; ++step) value = value * 1.01f + 0.1f;
        else
            for (int step = 0; step < 32; ++step) value = value * 0.99f - 0.1f;
        output[index] = value;
    }
}

void LaunchBranchPaths(const float* input, float* output, int count)
{
    BranchPathsKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch BranchPaths");
}
