#include "DeviceInfo.h"
#include <cuda_runtime.h>
#include <iostream>

void PrintDeviceInfo()
{
    int device_count = 0;
    cudaGetDeviceCount(&device_count);
    std::cout << "Visible devices: " << device_count << '\n';
    for (int device = 0; device < device_count; ++device)
    {
        cudaDeviceProp properties{};
        cudaGetDeviceProperties(&properties, device);
        std::cout << device << ": " << properties.name
                  << " CC " << properties.major << '.' << properties.minor
                  << " SMs=" << properties.multiProcessorCount
                  << " warp=" << properties.warpSize << '\n';
        std::cout << "Max block: " << properties.maxThreadsDim[0] << ' '
                  << properties.maxThreadsDim[1] << ' ' << properties.maxThreadsDim[2]
                  << "; max threads/block=" << properties.maxThreadsPerBlock << '\n';
        std::cout << "Max grid: " << properties.maxGridSize[0] << ' '
                  << properties.maxGridSize[1] << ' ' << properties.maxGridSize[2] << '\n';
        std::cout << "Global bytes=" << properties.totalGlobalMem
                  << " shared bytes/block=" << properties.sharedMemPerBlock << '\n';
    }
    if (device_count > 0)
        cudaSetDevice(0);
}
