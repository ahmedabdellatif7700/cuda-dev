#include <cuda_runtime.h>
#include <iostream>
int main()
{
    int count = 0;
    const auto status = cudaGetDeviceCount(&count);
    std::cout << "Device query: " << cudaGetErrorString(status) << "; visible devices=" << count << '\n';
    if (count < 2)
        std::cout << "Real P2P/multi-GPU execution unavailable: at least two compatible GPUs required.\n";
    for (int source = 0; source < count; ++source)
        for (int target = 0; target < count; ++target)
            if (source != target)
            {
                int supported = 0;
                cudaDeviceCanAccessPeer(&supported, source, target);
                std::cout << source << " -> " << target << ": " << supported << '\n';
            }
}
