#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void add (int *A, int *B,int *a) {
    int idx = blockIdx.x;
    printf("idx = %d\n", idx);
    A[idx] = (*a)*A[idx] + B[idx];
}

int main () {
    int M;
    int i, j;
    printf("Enter the size : ");
    scanf("%d",&M);
    int A[M], B[M];
    printf("Enter the X and Y values : \n");
    for (i = 0; i < M; ++i) { 
        scanf("%d%d",&A[i],&B[i]);
    }
    printf("Enter alpha : ");
    int a;
    scanf("%d",&a);
    int *d_a, *d_b, *d_c;
    int size = sizeof(int) * M;
    cudaMalloc((void**)&d_c,sizeof(int));
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMemcpy(d_a, &A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, &B, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, &a, sizeof(int), cudaMemcpyHostToDevice);
    add<<<M, 1>>>(d_a, d_b, d_c);
    cudaMemcpy(&A, d_a, size, cudaMemcpyDeviceToHost);
    printf("\n");
    printf("aA + B:\n");
    for (j = 0; j < M; ++j) {
        printf("%d\t", A[j]);
    }
    printf("\n");
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;
}