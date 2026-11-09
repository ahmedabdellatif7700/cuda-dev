#pragma once
#include <vector>
void NeighborReduce(std::vector<float>& output);
void LaunchNeighborReduce(const float* input, float* output, int count);
