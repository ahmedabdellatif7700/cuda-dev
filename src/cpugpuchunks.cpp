#include "CudaSupport.h"
#include "CpuGpuChunks.h"
#include <iostream>

void CpuGpuChunks(std::vector<float>& output)
{
    const int count = 1024;
    const int chunk_size = 256;
    float *host_input, *host_output, *device_input, *device_output;
    CheckCuda(cudaMallocHost(&host_input, count * sizeof(float)), "Pinned input");
    CheckCuda(cudaMallocHost(&host_output, count * sizeof(float)), "Pinned output");
    CheckCuda(cudaMalloc(&device_input, count * sizeof(float)), "Device input");
    CheckCuda(cudaMalloc(&device_output, count * sizeof(float)), "Device output");
    for (int index = 0; index < count; ++index) host_input[index] = 1.0f;
    cudaStream_t streams[4];
    cudaEvent_t complete[4];
    int low_priority, high_priority;
    cudaDeviceGetStreamPriorityRange(&low_priority, &high_priority);
    std::cout << "Priority range " << low_priority << ".." << high_priority << '\n';
    for (int chunk = 0; chunk < 4; ++chunk)
    {
        CheckCuda(cudaStreamCreateWithPriority(&streams[chunk], cudaStreamNonBlocking, low_priority), "Create stream");
        CheckCuda(cudaEventCreateWithFlags(&complete[chunk], cudaEventDisableTiming), "Create dependency event");
    }
    for (int chunk = 0; chunk < 4; ++chunk)
    {
        const int offset = chunk * chunk_size;
        CheckCuda(cudaMemcpyAsync(device_input + offset, host_input + offset, chunk_size * sizeof(float), cudaMemcpyHostToDevice, streams[chunk]), "Async input");
        LaunchCpuGpuChunks(device_input + offset, device_output + offset, chunk_size, streams[chunk]);
        CheckCuda(cudaMemcpyAsync(host_output + offset, device_output + offset, chunk_size * sizeof(float), cudaMemcpyDeviceToHost, streams[chunk]), "Async output");
    }
    for (int chunk = 0; chunk < 4; ++chunk)
    {
        CheckCuda(cudaEventRecord(complete[chunk], streams[chunk]), "Record dependency");
    }
    // Independent CPU work; output is not read until all events complete.
    int cpu_sum = 0;
    for (int index = 0; index < 100; ++index) cpu_sum += index;
    std::cout << "Independent CPU sum: " << cpu_sum << '\n';
    for (int chunk = 0; chunk < 4; ++chunk)
    {
        CheckCuda(cudaEventSynchronize(complete[chunk]), "Complete chunk");
        cudaEventDestroy(complete[chunk]);
        cudaStreamDestroy(streams[chunk]);
    }
    for (int index = 0; index < count; ++index) output[index] = host_output[index];
    cudaFree(device_input); cudaFree(device_output);
    cudaFreeHost(host_input); cudaFreeHost(host_output);
}
