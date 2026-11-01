#include "CudaSupport.h"
#include "VectorAdd.h"

void VectorAdd(const std::vector<float>& input_a, const std::vector<float>& input_b,
               std::vector<float>& output, int threads_per_block)
{
    if (input_a.size() != input_b.size() || input_a.size() != output.size())
        throw std::invalid_argument("Vector element_counts must match");
    if (threads_per_block < 1 || threads_per_block > 1024 || input_a.size() > (1u << 24))
        throw std::invalid_argument("Use at most 2^24 elements and 1..1024 threads_per_block");
    if (input_a.empty())
        return;

    const std::size_t element_count = input_a.size();
    const std::size_t byte_count = element_count * sizeof(float);
    DeviceBuffer device_a(element_count), device_b(element_count), device_output(element_count);
    CheckCuda(cudaMemcpy(device_a.data(), input_a.data(), byte_count, cudaMemcpyHostToDevice), "Copy A");
    CheckCuda(cudaMemcpy(device_b.data(), input_b.data(), byte_count, cudaMemcpyHostToDevice), "Copy B");

    LaunchVectorAddScalar(device_a.data(), device_b.data(), device_output.data(), element_count, threads_per_block);
    // Copying back waits for the kernel to finish.
    CheckCuda(cudaMemcpy(output.data(), device_output.data(), byte_count, cudaMemcpyDeviceToHost), "Copy result");
}

void VectorAddCyclic(const std::vector<float>& input_a, const std::vector<float>& input_b,
               std::vector<float>& output, int threads_per_block, int max_blocks)
{
    if (input_a.size() != input_b.size() || input_a.size() != output.size())
        throw std::invalid_argument("Vector element_counts must match");
    if (threads_per_block < 1 || threads_per_block > 1024 || input_a.size() > (1u << 24))
        throw std::invalid_argument("Use at most 2^24 elements and 1..1024 threads_per_block");
    if (max_blocks < 1)
        throw std::invalid_argument("Use at least one cyclic block");
    if (input_a.empty())
        return;

    const std::size_t element_count = input_a.size();
    const std::size_t byte_count = element_count * sizeof(float);
    DeviceBuffer device_a(element_count), device_b(element_count), device_output(element_count);
    CheckCuda(cudaMemcpy(device_a.data(), input_a.data(), byte_count, cudaMemcpyHostToDevice), "Copy A");
    CheckCuda(cudaMemcpy(device_b.data(), input_b.data(), byte_count, cudaMemcpyHostToDevice), "Copy B");

    LaunchVectorAddCyclic(device_a.data(), device_b.data(), device_output.data(), element_count, threads_per_block, max_blocks);
    // Copying back waits for the kernel to finish.
    CheckCuda(cudaMemcpy(output.data(), device_output.data(), byte_count, cudaMemcpyDeviceToHost), "Copy result");
}
