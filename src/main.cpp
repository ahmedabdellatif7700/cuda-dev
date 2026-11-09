#include "SparseProduct.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(2);
    SparseProduct(output);
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';
}
