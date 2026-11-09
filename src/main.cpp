#include <iostream>
int main()
{
#ifdef _OPENACC
    std::cout << "OpenACC version: " << _OPENACC << '\n';
#else
    std::cout << "Normal C++ build: OpenACC directives are not enabled.\n";
#endif
}
