#pragma once
#include <vector>
void ConstantStencil(std::vector<float>& output);
void LaunchConstantStencil(const float* input, float* output, int count);
