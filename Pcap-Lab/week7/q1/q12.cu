#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

#define M 6

__global__ void add (int *A, int *B, int *C) {
	int idx = threadIdx.x;
    printf("idx = %d\n", idx);
    C[idx] = A[idx] + B[idx];
}

int main () {
    int A[M], B[M], C[M];

    int i, j;
    for (i = 0; i < M; ++i) {
        A[i] = i + 1;
        B[i] = M - i - 1;
    }
    int *d_a, *d_b, *d_c;

    int size = sizeof(int) * M;
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);
    cudaMemcpy(d_a, &A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, &B, size, cudaMemcpyHostToDevice);
    add<<<1, M>>>(d_a, d_b, d_c);
    cudaMemcpy(&C, d_c, size, cudaMemcpyDeviceToHost);
    printf("A:\n");
    for (j = 0; j < M; ++j) {
        printf("%d\t", A[j]);
    }
    printf("\n");
    printf("B:\n");
    for (j = 0; j < M; ++j) {
        printf("%d\t", B[j]);
    }
    printf("\n");
    printf("A + B:\n");
    for (j = 0; j < M; ++j) {
        printf("%d\t", C[j]);
    }
    printf("\n");

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

	getchar();

    return 0;
}