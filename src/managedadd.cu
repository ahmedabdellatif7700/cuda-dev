#include "CudaSupport.h"
#include "ManagedAdd.h"

__global__ void ManagedAddKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd5];  // Read global data.
    // add.f32 %f2, %f1, 0f40000000;  // Add float values.
    // st.global.f32 [%rd7], %f2;  // Write global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count) output[index] = input[index] + 2.0f;
}

void LaunchManagedAdd(const float* input, float* output, int count)
{
    ManagedAddKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch ManagedAdd");
}
