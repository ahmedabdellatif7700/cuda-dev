#include "CudaSupport.h"
#include "ManagedAdd.h"
void ManagedAdd(std::vector<float>& output)
{
    const int count = int(output.size());
    float *input, *result;
    CheckCuda(cudaMallocManaged(&input, count * sizeof(float)), "Managed input");
    CheckCuda(cudaMallocManaged(&result, count * sizeof(float)), "Managed output");
    for (int index = 0; index < count; ++index) input[index] = 1.0f;
    LaunchManagedAdd(input, result, count);
    CheckCuda(cudaDeviceSynchronize(), "Complete managed work");
    for (int index = 0; index < count; ++index) output[index] = result[index];
    cudaFree(input);
    cudaFree(result);
}
