#include "CudaSupport.h"
#include "IdeaBlocks.h"

__constant__ unsigned short round_keys[52];

__device__ unsigned short MultiplyIdea(unsigned short a, unsigned short b)
{
    // IDEA represents 65536 by the 16-bit value zero.
    const unsigned long long x = a == 0 ? 65536ULL : a;
    const unsigned long long y = b == 0 ? 65536ULL : b;
    return static_cast<unsigned short>((x * y) % 65537ULL);
}

__global__ void EncryptIdeaBlocks(const unsigned short* input, unsigned short* output, int blocks)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.u16 %rs45, [%rd11+6];  // Read global data.
    // ld.global.u16 %rs46, [%rd11+4];  // Read global data.
    // ld.global.u16 %rs47, [%rd11+2];  // Read global data.
    const int block = blockIdx.x * blockDim.x + threadIdx.x;
    if (block >= blocks) return;
    const int offset = block * 4;
    unsigned short x1 = input[offset], x2 = input[offset + 1];
    unsigned short x3 = input[offset + 2], x4 = input[offset + 3];
    int key = 0;
    for (int round = 0; round < 8; ++round)
    {
        x1 = MultiplyIdea(x1, round_keys[key++]);
        x2 = static_cast<unsigned short>(x2 + round_keys[key++]);
        x3 = static_cast<unsigned short>(x3 + round_keys[key++]);
        x4 = MultiplyIdea(x4, round_keys[key++]);
        unsigned short t0 = MultiplyIdea(x1 ^ x3, round_keys[key++]);
        const unsigned short t1 = MultiplyIdea(static_cast<unsigned short>((x2 ^ x4) + t0), round_keys[key++]);
        t0 = static_cast<unsigned short>(t0 + t1);
        x1 ^= t1; x4 ^= t0;
        const unsigned short old_x2 = x2;
        x2 = x3 ^ t1; x3 = old_x2 ^ t0;
    }
    output[offset] = MultiplyIdea(x1, round_keys[48]);
    output[offset + 1] = static_cast<unsigned short>(x3 + round_keys[49]);
    output[offset + 2] = static_cast<unsigned short>(x2 + round_keys[50]);
    output[offset + 3] = MultiplyIdea(x4, round_keys[51]);
}

void UploadIdeaKeys(const unsigned short* keys)
{
    CheckCuda(cudaMemcpyToSymbol(round_keys, keys, 52 * sizeof(unsigned short)), "Upload round keys");
}

void LaunchIdeaBlocks(const unsigned short* input, unsigned short* output, int blocks)
{
    EncryptIdeaBlocks<<<(blocks + 127) / 128, 128>>>(input, output, blocks);
    CheckCuda(cudaGetLastError(), "Launch IDEA");
}
