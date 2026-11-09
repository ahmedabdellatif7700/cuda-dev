#include "CudaSupport.h"
#include "TransformValues.h"
#include <vector>

void TransformValues(std::vector<float>& output)
{
    const int count = 1024;
    std::vector<float> input(count, 1.0f);
    DeviceBuffer device_input(count), device_output(output.size());
    CheckCuda(cudaMemcpy(device_input.data(), input.data(), count * sizeof(float), cudaMemcpyHostToDevice), "Copy input");
    LaunchTransformValues(device_input.data(), device_output.data(), count);
    CheckCuda(cudaMemcpy(output.data(), device_output.data(), output.size() * sizeof(float), cudaMemcpyDeviceToHost), "Copy output");
}
