#include "CudaSupport.h"
#include "ThreadMapping.h"

__global__ void WriteThreadIndices(float* output)
{
    const int global_index = blockIdx.x * blockDim.x + threadIdx.x;
    output[global_index] = static_cast<float>(global_index);
}

void LaunchThreadMapping(float* output, int block_count, int threads_per_block)
{
    WriteThreadIndices<<<block_count, threads_per_block>>>(output);
    CheckCuda(cudaGetLastError(), "Launch WriteThreadIndices");
}
