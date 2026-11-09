#include "CudaSupport.h"
#include "PaddedTranspose.h"
#include <vector>

void PaddedTranspose(std::vector<float>& output)
{
    const int count = 64;
    std::vector<float> input(count);
    for (int index = 0; index < count; ++index) input[index] = float(index);
    DeviceBuffer device_input(count), device_output(output.size());
    CheckCuda(cudaMemcpy(device_input.data(), input.data(), count * sizeof(float), cudaMemcpyHostToDevice), "Copy input");
    LaunchPaddedTranspose(device_input.data(), device_output.data(), count);
    CheckCuda(cudaMemcpy(output.data(), device_output.data(), output.size() * sizeof(float), cudaMemcpyDeviceToHost), "Copy output");
}
