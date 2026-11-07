#include "CudaSupport.h"
#include "MatrixAdd.h"

void MatrixAdd2D(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& output, int width, int height, int block_x, int block_y)
{
    const std::size_t count = output.size();
    const std::size_t bytes = count * sizeof(float);
    DeviceBuffer device_a(count), device_b(count), device_output(count);
    cudaMemcpy(device_a.data(), a.data(), bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(device_b.data(), b.data(), bytes, cudaMemcpyHostToDevice);
    LaunchMatrixAdd2D(device_a.data(), device_b.data(), device_output.data(), width, height, block_x, block_y);
    cudaMemcpy(output.data(), device_output.data(), bytes, cudaMemcpyDeviceToHost);
}
