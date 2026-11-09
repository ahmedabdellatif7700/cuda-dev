#pragma once
#include <vector>
void StridedRead(std::vector<float>& output);
void LaunchStridedRead(const float* input, float* output, int count);
