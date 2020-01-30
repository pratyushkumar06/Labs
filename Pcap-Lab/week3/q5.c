#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc , char* argv[])
{
	int rank , size , N = 1 , M = 0 , nonvow =0,sum=0;
	int* arr = (int*)malloc(sizeof(char)*(M));
	int* arr3 = (int*)malloc(sizeof(int)*M);
	MPI_Init(&argc ,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0)
	{
		N = size;
		printf("Enter the value of M \n");
		scanf("%d",&M);
		
		printf("Enter the numbers\n");
			for(int i = 0;i<M;i++)
				scanf("%d",&arr[i]);

		printf("The input array is \n");
		for(int i = 0;i<M;i++)
		{
			printf("%d \t",arr[i]);
		}
		printf("\n");
	}
	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	int div = M/N;
	int* sub = (int*)malloc(sizeof(int)*(div));
	//printf("M = %d \t N = %d \t  Div = %d \n ",M,N,div);
	MPI_Scatter(arr,div,MPI_INT , sub ,div,MPI_INT,0,MPI_COMM_WORLD);
	fflush(stdout);
	printf("I have received the below values in process %d \n",rank);
	for(int i = 0;i<div;i++)
	{
		printf("%d \t",sub[i]);
	}
	printf("\n");
	for(int i = 0;i<div;i++)
	{
		if(sub[i]%2 == 0)
			sub[i] = 1;
		else
			sub[i] = 0;
	}
	MPI_Gather(sub,div,MPI_INT,arr3,div,MPI_INT,0,MPI_COMM_WORLD);
	if(rank == 0)
	{
		printf("The Result gathered in the root \n ");
		for(int i =0;i<M;i++)
		{
			printf("%d \t",arr3[i]);
		}

		printf("\n");

	}


}