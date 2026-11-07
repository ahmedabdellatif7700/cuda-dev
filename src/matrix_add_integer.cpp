#include "CudaSupport.h"
#include "MatrixAdd.h"

void MatrixAddInteger(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& output, int width, int height, int block_x, int block_y)
{
    const std::size_t bytes = output.size() * sizeof(int);
    int *device_a, *device_b, *device_output;
    cudaMalloc(&device_a, bytes);
    cudaMalloc(&device_b, bytes);
    cudaMalloc(&device_output, bytes);
    cudaMemcpy(device_a, a.data(), bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(device_b, b.data(), bytes, cudaMemcpyHostToDevice);
    LaunchMatrixAddInteger(device_a, device_b, device_output, width, height, block_x, block_y);
    cudaMemcpy(output.data(), device_output, bytes, cudaMemcpyDeviceToHost);
    cudaFree(device_a);
    cudaFree(device_b);
    cudaFree(device_output);
}
