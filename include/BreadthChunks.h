#pragma once
#include <vector>
#include <cuda_runtime.h>
void BreadthChunks(std::vector<float>& output);
void LaunchBreadthChunks(const float* input, float* output, int count, cudaStream_t stream);
