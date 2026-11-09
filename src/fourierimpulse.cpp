#include "CudaSupport.h"
#include "FourierImpulse.h"
#include <cufft.h>
void FourierImpulse(std::vector<float>& output)
{
    cufftComplex input[8] = {};
    input[0].x = 1.0f;
    cufftComplex* device;
    CheckCuda(cudaMalloc(&device, sizeof(input)), "FFT allocation");
    CheckCuda(cudaMemcpy(device, input, sizeof(input), cudaMemcpyHostToDevice), "FFT input");
    cufftHandle plan;
    if (cufftPlan1d(&plan, 8, CUFFT_C2C, 1) != CUFFT_SUCCESS) throw std::runtime_error("FFT plan failed");
    if (cufftExecC2C(plan, device, device, CUFFT_FORWARD) != CUFFT_SUCCESS) throw std::runtime_error("FFT failed");
    CheckCuda(cudaMemcpy(input, device, sizeof(input), cudaMemcpyDeviceToHost), "FFT result");
    for (int index = 0; index < 8; ++index) output[index] = input[index].x;
    cufftDestroy(plan);
    cudaFree(device);
}
