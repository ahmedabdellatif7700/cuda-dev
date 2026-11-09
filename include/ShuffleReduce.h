#pragma once
#include <vector>
void ShuffleReduce(std::vector<float>& output);
void LaunchShuffleReduce(const float* input, float* output, int count);
