#include "CudaSupport.h"
#include "VectorAdd.h"

// Each thread computes one independent output element.
__global__ void VectorAddScalar(const float* input_a, const float* input_b, float* output, std::size_t element_count)
{
    const auto index = std::size_t(blockIdx.x) * blockDim.x + threadIdx.x;
    if (index < element_count)
        output[index] = input_a[index] + input_b[index];
}

void LaunchVectorAddScalar(const float* input_a, const float* input_b, float* output,
                           std::size_t element_count, int threads_per_block)
{
    if (element_count == 0)
        return;
    const auto block_count = static_cast<unsigned>((element_count + threads_per_block - 1) / threads_per_block);
    VectorAddScalar<<<block_count, threads_per_block>>>(input_a, input_b, output, element_count);
    CheckCuda(cudaGetLastError(), "Launch VectorAddScalar");
}
