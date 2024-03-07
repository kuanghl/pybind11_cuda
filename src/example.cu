#include <cuda_runtime.h>

__global__ void addKernel(int *c, const int *a, const int *b, int size) {
    int i = threadIdx.x;
    if (i < size) {
        c[i] = a[i] + b[i];
    }
}

void add(int *c, const int *a, const int *b, int size) {
    int *dev_a, *dev_b, *dev_c;
    cudaMalloc((void**)&dev_a, size * sizeof(int));
    cudaMalloc((void**)&dev_b, size * sizeof(int));
    cudaMalloc((void**)&dev_c, size * sizeof(int));

    cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);

    addKernel<<<1, size>>>(dev_c, dev_a, dev_b, size);

    cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
}
