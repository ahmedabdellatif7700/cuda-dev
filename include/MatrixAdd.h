#pragma once
#include <vector>

// Row-major arrays must each hold width * height elements.
void MatrixAdd2D(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& output, int width, int height, int block_x, int block_y);
void MatrixAdd1D(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& output, int width, int height, int threads);
void MatrixAddRows(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& output, int width, int height, int threads);
void MatrixAddPairs(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& output, int width, int height, int threads);
void MatrixAddInteger(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& output, int width, int height, int block_x, int block_y);

// Launch wrappers accept device pointers. Positive dimensions are required.
void LaunchMatrixAdd2D(const float*, const float*, float*, int, int, int, int);
void LaunchMatrixAdd1D(const float*, const float*, float*, int, int, int);
void LaunchMatrixAddRows(const float*, const float*, float*, int, int, int);
void LaunchMatrixAddPairs(const float*, const float*, float*, int, int, int);
void LaunchMatrixAddInteger(const int*, const int*, int*, int, int, int, int);
