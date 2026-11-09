#include "CudaSupport.h"
#include "CopyGlobal.h"

__global__ void CopyGlobalKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd5];  // Read global data.
    // st.global.f32 [%rd7], %f1;  // Write global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count) output[index] = input[index];
}

void LaunchCopyGlobal(const float* input, float* output, int count)
{
    CopyGlobalKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch CopyGlobal");
}
