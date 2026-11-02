#include "CudaSupport.h"
#include "VectorAdd.h"

void VectorAdd(const std::vector<float>& input_a, const std::vector<float>& input_b,
               std::vector<float>& output, int threads_per_block)
{
    const std::size_t element_count = output.size();
    const std::size_t byte_count = element_count * sizeof(float);
    DeviceBuffer device_a(element_count), device_b(element_count), device_output(element_count);

    cudaMemcpy(device_a.data(), input_a.data(), byte_count, cudaMemcpyHostToDevice);
    cudaMemcpy(device_b.data(), input_b.data(), byte_count, cudaMemcpyHostToDevice);

    LaunchVectorAddScalar(device_a.data(), device_b.data(), device_output.data(),
                          element_count, threads_per_block);
    cudaMemcpy(output.data(), device_output.data(), byte_count, cudaMemcpyDeviceToHost);
}
