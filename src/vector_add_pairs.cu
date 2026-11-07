#include "CudaSupport.h"
#include "VectorAdd.h"

__global__ void AddVectorPairs(const float* a, const float* b, float* output, std::size_t count)
{
    const std::size_t index = std::size_t(blockIdx.x) * (2 * blockDim.x) + threadIdx.x;
    if (index < count)
        // Selected generated PTX; address/branch setup omitted.
        // ld.global.f32 %f1, [%rd14];  // Load an input element.
        // ld.global.f32 %f2, [%rd13];  // Load an input element.
        // add.f32 %f3, %f2, %f1;  // Add the two input values.
        // st.global.f32 [%rd15], %f3;  // Store this output element.
        output[index] = a[index] + b[index];
    if (index + blockDim.x < count)
        output[index + blockDim.x] = a[index + blockDim.x] + b[index + blockDim.x];
}

void LaunchVectorAddPairs(const float* a, const float* b, float* output, std::size_t count, int threads)
{
    if (count == 0) return;
    const unsigned blocks = (count + 2 * threads - 1) / (2 * threads);
    AddVectorPairs<<<blocks, threads>>>(a, b, output, count);
    CheckCuda(cudaGetLastError(), "Launch AddVectorPairs");
}
