#pragma once

#include <vector>

// Host function: allocate device storage, run the mapping kernel, and copy back.
// Each output value is the global index of the thread that wrote it.
// The caller must size output to block_count * threads_per_block.
void ThreadMapping(std::vector<float>& output, int block_count, int threads_per_block);

// CUDA launch wrapper: output is a device pointer with space for every thread.
// The launch uses block_count blocks with threads_per_block threads in each.
void LaunchThreadMapping(float* output, int block_count, int threads_per_block);
