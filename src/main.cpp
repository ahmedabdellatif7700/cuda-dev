#include "BankStride.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(256);
    BankStride(output);
    std::cout << "BankStride: ";
    for (int index = 0; index < 8 && index < int(output.size()); ++index)
        std::cout << output[index] << ' ';
    std::cout << '\n';
}
