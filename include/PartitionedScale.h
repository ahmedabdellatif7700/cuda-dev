#pragma once
#include <vector>
void PartitionedScale(std::vector<float>& output);
void LaunchPartitionedScale(const float* input, float* output, int count);
