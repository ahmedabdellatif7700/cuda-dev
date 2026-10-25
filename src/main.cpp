#include "Lesson.h"
#include <cmath>
#include <exception>
#include <iostream>
#include <vector>

int main()
{
    try
    {
        // Empty, tiny, block boundaries, and multiple blocks.
        for (std::size_t n : {0u, 1u, 10u, 255u, 256u, 257u, 1000u, 65537u})
        {
            std::vector<float> a(n), b(n), c(n);
            for (std::size_t i = 0; i < n; ++i)
            {
                a[i] = float(i % 17);
                b[i] = float(i % 11);
            }

            VectorAdd(a.data(), b.data(), c.data(), n);

            for (std::size_t i = 0; i < n; ++i)
            {
                const float expected = a[i] + b[i];
                if (!std::isfinite(c[i]) || std::fabs(c[i] - expected) > 1e-5f)
                {
                    std::cerr << "FAIL: n=" << n << ", index=" << i << '\n';
                    return 1;
                }
            }
            std::cout << "PASS: " << n << " elements\n";
        }
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
