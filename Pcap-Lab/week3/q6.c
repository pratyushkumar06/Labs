#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc , char* argv[])
{
	int rank , size , N , M = 4,sum=0,avg;
	int* arr1 = (int*)malloc(sizeof(int)*(N*M));
	int* arr2 = (int*)malloc(sizeof(int)*M);
	int* arr3 = (int*)malloc(sizeof(int)*(N*M));
	MPI_Init(&argc ,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0)
	{
		N = size;
		printf("Enter value of M \n");
		scanf("%d",&M);
		printf("Enter %d values \n",N*M);
		for(int i =0;i<(N*M);i++)
			scanf("%d",&arr1[i]);

	}
	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr1,M,MPI_INT,arr2,M,MPI_INT,0,MPI_COMM_WORLD);
	printf("I have received the below values in process %d \n",rank);
	printf("%d \t",arr2[0]);
	for(int i =1;i<M;i++)
	{
		printf("%d \t ",arr2[i]);
		arr2[i] += arr2[i-1];
	}
	printf("\n");
	fflush(stdout);
	MPI_Gather(arr2,M,MPI_INT,arr3,M,MPI_INT,0,MPI_COMM_WORLD);
	if(rank == 0)
	{
		printf("The Result gathered in the root \n ");
		for(int i =0;i<(M*N);i++)
		{
			printf("%d \t",arr3[i]);
		}
		printf("\n");

	}



}