#include "DeviceInfo.h"
#include "MatrixAdd.h"
#include "VectorAdd.h"
#include <iostream>
#include <vector>

int main()
{
    PrintDeviceInfo();
    const int width = 7;
    const int height = 3;
    const int count = width * height;
    std::vector<float> a(count), b(count, 10.0f), output(count);
    for (int index = 0; index < count; ++index)
        a[index] = static_cast<float>(index);

    VectorAdd(a, b, output, 256);
    std::cout << "Scalar vector: ";
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';

    VectorAddPairs(a, b, output, 256);
    std::cout << "Two elements/thread: ";
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';

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

    MatrixAddPairs(a, b, output, width, height, 4);
    std::cout << "Two columns/thread: ";
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';

    std::vector<int> integer_a(count, 2), integer_b(count, 3), integer_output(count);
    MatrixAddInteger(integer_a, integer_b, integer_output, width, height, 4, 2);
    std::cout << "Integer matrix: ";
    for (int value : integer_output) std::cout << value << ' ';
    std::cout << '\n';
}
