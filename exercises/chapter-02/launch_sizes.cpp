#include "VectorAdd.h"
#include <iostream>
#include <vector>

int main()
{
    std::vector<float> a(2051, 1), b(2051, 2), output(2051);
    for (int threads : {1023, 1024})
    {
        VectorAdd(a, b, output, threads);
        std::cout << "Threads/block " << threads << ": " << output.front() << ' ' << output.back() << '\n';
    }
}
