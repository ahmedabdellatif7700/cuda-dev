#include "VectorAdd.h"

#include <array>
#include <exception>
#include <iostream>
#include <vector>

int main()
{
    constexpr int threads = 256;
    constexpr std::array<std::size_t, 9> sizes{0, 1, 16, 31, 33, 257, 1024, 65536, 4194307};

    try
    {
        for (const auto n : sizes)
        {
            std::vector<float> a(n), b(n), result(n);
            for (std::size_t i = 0; i < n; ++i)
            {
                a[i] = static_cast<float>(i % 17) * 0.25f;
                b[i] = static_cast<float>(i % 11) * -0.5f;
            }

            VectorAdd(a, b, result, threads);

            std::cout << "Completed n=" << n << " threads=" << threads << '\n';
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
