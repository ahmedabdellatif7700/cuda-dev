#pragma once
#include <vector>
void BankStride(std::vector<float>& output);
void LaunchBankStride(const float* input, float* output, int count);
