#include "CudaSupport.h"
#include "AtomicSum.h"

__global__ void AtomicSumKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd5];  // Read global data.
    // atom.global.add.f32 %f2, [%rd6], %f1;  // Atomic global update.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count) atomicAdd(output, input[index]);
}

void LaunchAtomicSum(const float* input, float* output, int count)
{
    AtomicSumKernel<<<(count + 255) / 256, 256>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch AtomicSum");
}
