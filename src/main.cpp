#include "MatrixAdd.h"
#include <iostream>
#include <vector>

int main()
{
    const int width = 7;
    const int height = 3;
    const int count = width * height;
    std::vector<float> a(count), b(count, 10.0f), output(count);
    for (int index = 0; index < count; ++index)
        a[index] = static_cast<float>(index);

    MatrixAdd2D(a, b, output, width, height, 4, 2);
    std::cout << "2D grid / 2D blocks:\n";
    for (int index = 0; index < count; ++index)
    {
        std::cout << output[index] << ' ';
        if ((index + 1) % width == 0) std::cout << '\n';
    }
    MatrixAdd1D(a, b, output, width, height, 8);
    std::cout << "1D grid / 1D blocks: ";
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';
    MatrixAddRows(a, b, output, width, height, 4);
    std::cout << "2D grid / 1D blocks: ";
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';
}
