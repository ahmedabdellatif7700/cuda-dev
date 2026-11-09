#include "CudaSupport.h"
#include "IdeaBlocks.h"

void IdeaBlocks(std::vector<unsigned short>& output)
{
    unsigned short key[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    unsigned short expanded[52];
    int produced = 0;
    while (produced < 52)
    {
        for (int index = 0; index < 8 && produced < 52; ++index)
            expanded[produced++] = key[index];
        unsigned short rotated[8];
        for (int index = 0; index < 8; ++index)
            rotated[index] = static_cast<unsigned short>((unsigned(key[(index + 1) % 8]) << 9)
                                                       | (unsigned(key[(index + 2) % 8]) >> 7));
        for (int index = 0; index < 8; ++index) key[index] = rotated[index];
    }
    UploadIdeaKeys(expanded);
    const unsigned short input[4] = {0, 1, 2, 3};
    unsigned short *device_input, *device_output;
    CheckCuda(cudaMalloc(&device_input, sizeof(input)), "IDEA input");
    CheckCuda(cudaMalloc(&device_output, sizeof(input)), "IDEA output");
    CheckCuda(cudaMemcpy(device_input, input, sizeof(input), cudaMemcpyHostToDevice), "Copy block");
    LaunchIdeaBlocks(device_input, device_output, 1);
    CheckCuda(cudaMemcpy(output.data(), device_output, sizeof(input), cudaMemcpyDeviceToHost), "Copy cipher block");
    cudaFree(device_input); cudaFree(device_output);
}
