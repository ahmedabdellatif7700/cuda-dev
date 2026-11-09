#pragma once
#include <vector>
void SharedReduce(std::vector<float>& output);
void LaunchSharedReduce(const float* input, float* output, int count);
