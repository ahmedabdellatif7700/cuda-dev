#include "CudaSupport.h"
#include "ThreadMapping.h"

void ThreadMapping(std::vector<float>& output, int block_count, int threads_per_block)
{
    const std::size_t byte_count = output.size() * sizeof(float);
    DeviceBuffer device_output(output.size());

    LaunchThreadMapping(device_output.data(), block_count, threads_per_block);
    cudaMemcpy(output.data(), device_output.data(), byte_count, cudaMemcpyDeviceToHost);
}
