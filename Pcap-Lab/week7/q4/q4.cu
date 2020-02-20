#include<stdio.h>
#include<cuda.h>
#include<cuda_runtime_api.h>

__global__ void AddIntsCUDA(int *a, int *b,int *d) //Kernel Definition
{
 *a = (*a)*(*d) + *b;
}

int main()
{
 int a = 5, b = 9,d=2;
 int *d_a, *d_b,*d_d; //Device variable Declaration

        //Allocation of Device Variables 
 cudaMalloc((void **)&d_a, sizeof(int));
 cudaMalloc((void **)&d_b, sizeof(int));
 cudaMalloc((void **)&d_d, sizeof(int));
        //Copy Host Memory to Device Memory
 cudaMemcpy(d_a, &a, sizeof(int), cudaMemcpyHostToDevice);
 cudaMemcpy(d_b, &b, sizeof(int), cudaMemcpyHostToDevice);
 cudaMemcpy(d_d, &d, sizeof(int), cudaMemcpyHostToDevice);
        
        //Launch Kernel
 AddIntsCUDA << <1, 1 >> >(d_a, d_b,d_d);

        //Copy Device Memory to Host Memory
 cudaMemcpy(&a, d_a, sizeof(int), cudaMemcpyDeviceToHost);

 printf("The answer is %d",a);

 
        //Free Device Memory
        cudaFree(d_a);
        cudaFree(d_b);
        cudaFree(d_d);

 return 0;
}