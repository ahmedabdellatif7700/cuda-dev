#pragma once
#include <vector>
void InterleavedReduce(std::vector<float>& output);
void LaunchInterleavedReduce(const float* input, float* output, int count);
