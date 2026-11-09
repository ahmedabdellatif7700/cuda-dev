#include <iostream>
#ifdef _OPENACC
#include <openacc.h>
#endif
int main()
{
    const int count = 64;
    float a[count], b[count], output[count];
    for (int index = 0; index < count; ++index) { a[index] = 1; b[index] = 2; }
    #pragma acc data copyin(a[0:count], b[0:count]) copyout(output[0:count])
    {
        #pragma acc parallel loop
        for (int index = 0; index < count; ++index) output[index] = a[index] + b[index];
    }
    for (int index = 0; index < 8; ++index) std::cout << output[index] << ' ';
#ifdef _OPENACC
    std::cout << " OpenACC devices: " << acc_get_num_devices(acc_device_default);
#endif
    std::cout << '\n';
}
