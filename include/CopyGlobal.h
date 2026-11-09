#pragma once
#include <vector>
void CopyGlobal(std::vector<float>& output);
void LaunchCopyGlobal(const float* input, float* output, int count);
