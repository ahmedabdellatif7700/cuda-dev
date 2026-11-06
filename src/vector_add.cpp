#include "CudaSupport.h"
#include "VectorAdd.h"

#include <iostream>

void VectorAdd(const std::vector<float>& input_a, const std::vector<float>& input_b,
               std::vector<float>& output, int threads_per_block)
{
    const std::size_t element_count = output.size();
    const std::size_t byte_count = element_count * sizeof(float);
    // CPU code requests storage for the GPU.
    std::cout << "CPU: allocate GPU buffers\n";
    DeviceBuffer device_a(element_count), device_b(element_count), device_output(element_count);

    // Copy host inputs into the device allocations.
    std::cout << "CPU -> GPU: copy inputs\n";
    cudaMemcpy(device_a.data(), input_a.data(), byte_count, cudaMemcpyHostToDevice);
    cudaMemcpy(device_b.data(), input_b.data(), byte_count, cudaMemcpyHostToDevice);

    // This host call submits work; the kernel body runs on the GPU.
    std::cout << "CPU: submit vector-add kernel to GPU\n";
    LaunchVectorAddScalar(device_a.data(), device_b.data(), device_output.data(),
                          element_count, threads_per_block);
    // The blocking copy waits for the result before returning to main.
    std::cout << "GPU -> CPU: copy results and wait for completion\n";
    cudaMemcpy(output.data(), device_output.data(), byte_count, cudaMemcpyDeviceToHost);
}
