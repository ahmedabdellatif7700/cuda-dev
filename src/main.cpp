#include "TransposeMatrix.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(64);
    TransposeMatrix(output);
    std::cout << "TransposeMatrix: ";
    for (int index = 0; index < 8 && index < int(output.size()); ++index)
        std::cout << output[index] << ' ';
    std::cout << '\n';
}
