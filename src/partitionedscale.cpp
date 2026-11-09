#include "CudaSupport.h"
#include "PartitionedScale.h"
#include <vector>

void PartitionedScale(std::vector<float>& output)
{
    const int count = 1024;
    std::vector<float> input(count, 1.0f);
    DeviceBuffer device_input(count), device_output(output.size());
    CheckCuda(cudaMemcpy(device_input.data(), input.data(), count * sizeof(float), cudaMemcpyHostToDevice), "Copy input");
    // Two real local subdomains, on the same GPU. This is not multi-GPU evidence.
    const int first_count = count / 2;
    LaunchPartitionedScale(device_input.data(), device_output.data(), first_count);
    LaunchPartitionedScale(device_input.data() + first_count, device_output.data() + first_count, count - first_count);
    CheckCuda(cudaMemcpy(output.data(), device_output.data(), output.size() * sizeof(float), cudaMemcpyDeviceToHost), "Copy output");
}
