#include "CudaSupport.h"
#include "StreamReview.h"

__global__ void StreamReviewKernel(const float* input, float* output, int count)
{
    // Selected generated PTX; intervening setup/control instructions omitted.
    // ld.global.f32 %f1, [%rd5];  // Read global data.
    // add.f32 %f2, %f1, %f1;  // Add float values.
    // st.global.f32 [%rd7], %f2;  // Write global data.
    const int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < count) output[index] = input[index] * 2.0f;
}

void LaunchStreamReview(const float* input, float* output, int count, cudaStream_t stream)
{
    StreamReviewKernel<<<(count + 255) / 256, 256, 0, stream>>>(input, output, count);
    CheckCuda(cudaGetLastError(), "Launch StreamReview");
}
