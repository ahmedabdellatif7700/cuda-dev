#include "CudaSupport.h"
#include "AtomicSum.h"
#include <vector>

void AtomicSum(std::vector<float>& output)
{
    const int count = 1024;
    std::vector<float> input(count, 1.0f);
    DeviceBuffer device_input(count), device_output(output.size());
    CheckCuda(cudaMemcpy(device_input.data(), input.data(), count * sizeof(float), cudaMemcpyHostToDevice), "Copy input");
    CheckCuda(cudaMemset(device_output.data(), 0, sizeof(float)), "Clear sum");
    LaunchAtomicSum(device_input.data(), device_output.data(), count);
    CheckCuda(cudaMemcpy(output.data(), device_output.data(), output.size() * sizeof(float), cudaMemcpyDeviceToHost), "Copy output");
}
