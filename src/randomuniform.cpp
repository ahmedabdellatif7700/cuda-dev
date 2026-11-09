#include "CudaSupport.h"
#include "RandomUniform.h"
#include <curand.h>
void RandomUniform(std::vector<float>& output)
{
    DeviceBuffer device_output(output.size());
    curandGenerator_t generator;
    if (curandCreateGenerator(&generator, CURAND_RNG_PSEUDO_DEFAULT) != CURAND_STATUS_SUCCESS)
        throw std::runtime_error("Create RNG");
    curandSetPseudoRandomGeneratorSeed(generator, 1234ULL);
    if (curandGenerateUniform(generator, device_output.data(), output.size()) != CURAND_STATUS_SUCCESS)
        throw std::runtime_error("Generate RNG");
    CheckCuda(cudaMemcpy(output.data(), device_output.data(), output.size() * sizeof(float), cudaMemcpyDeviceToHost), "RNG output");
    curandDestroyGenerator(generator);
}
