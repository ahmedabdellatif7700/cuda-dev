#include "BlasProduct.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(4);
    BlasProduct(output);
    for (float value : output) std::cout << value << ' ';
    std::cout << '\n';
}
