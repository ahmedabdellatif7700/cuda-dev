#include "NeighborReduce.h"
#include "InterleavedReduce.h"
#include <iostream>
#include <vector>
int main()
{
    std::vector<float> output(1);
    NeighborReduce(output);
    std::cout << "NeighborReduce: " << output[0] << '\n';
    InterleavedReduce(output);
    std::cout << "InterleavedReduce: " << output[0] << '\n';
}
