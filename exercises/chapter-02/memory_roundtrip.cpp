#include <cuda_runtime.h>
#include <iostream>
#include <vector>

int main()
{
    std::vector<float> input{1, 2, 3, 4}, output(4);
    float* device;
    const std::size_t bytes = input.size() * sizeof(float);
    cudaMalloc(&device, bytes);
    cudaMemcpy(device, input.data(), bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(output.data(), device, bytes, cudaMemcpyDeviceToHost);
    cudaFree(device);
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';
}
