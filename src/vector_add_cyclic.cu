#include "CudaSupport.h"
#include "VectorAdd.h"

#include <algorithm>

// Adjacent threads_per_block start at adjacent elements, then jump by the whole grid.
__global__ void VectorAddCyclic(const float* input_a, const float* input_b, float* output, std::size_t element_count)
{
    const auto first_index = std::size_t(blockIdx.x) * blockDim.x + threadIdx.x;
    const auto grid_stride = std::size_t(gridDim.x) * blockDim.x;
    for (auto index = first_index; index < element_count; index += grid_stride)
        output[index] = input_a[index] + input_b[index];
}

void LaunchVectorAddCyclic(const float* input_a, const float* input_b, float* output,
                          std::size_t element_count, int threads_per_block, int max_blocks)
{
    if (element_count == 0)
        return;
    const auto required_blocks = (element_count + threads_per_block - 1) / threads_per_block;
    const auto block_count = static_cast<unsigned>(std::min(required_blocks, std::size_t(max_blocks)));
    VectorAddCyclic<<<block_count, threads_per_block>>>(input_a, input_b, output, element_count);
    CheckCuda(cudaGetLastError(), "Launch VectorAddCyclic");
}
