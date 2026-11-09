#include "CudaSupport.h"
#include "PartitionedScale.h"

__global__ void PartitionedScaleKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd5];  // Read global data.
    // add.f32 %f2, %f1, %f1;  // Add float values.
    // st.global.f32 [%rd7], %f2;  // Write global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count) output[index] = 2.0f * input[index];
}

void LaunchPartitionedScale(const float* input, float* output, int count)
{
    PartitionedScaleKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch PartitionedScale");
}
