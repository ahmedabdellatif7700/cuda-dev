#pragma once
#include <vector>

// Caller supplies row-major arrays of width * height elements.
void MatrixAdd2D(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& output, int width, int height, int block_x, int block_y);
void MatrixAdd1D(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& output, int width, int height, int threads);
void LaunchMatrixAdd2D(const float*, const float*, float*, int, int, int, int);
void LaunchMatrixAdd1D(const float*, const float*, float*, int, int, int);
