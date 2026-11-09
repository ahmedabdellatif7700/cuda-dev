#include "CudaSupport.h"
#include "TransposeMatrix.h"
#include <vector>

void TransposeMatrix(std::vector<float>& output)
{
    const int count = 64;
    std::vector<float> input(count);
    for (int index = 0; index < count; ++index) input[index] = float(index);
    DeviceBuffer device_input(count), device_output(output.size());
    CheckCuda(cudaMemcpy(device_input.data(), input.data(), count * sizeof(float), cudaMemcpyHostToDevice), "Copy input");
    LaunchTransposeMatrix(device_input.data(), device_output.data(), count);
    CheckCuda(cudaMemcpy(output.data(), device_output.data(), output.size() * sizeof(float), cudaMemcpyDeviceToHost), "Copy output");
}
