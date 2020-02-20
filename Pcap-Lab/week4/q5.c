#include "mpi.h"
#include <stdio.h>
#include "ErrorHandler.h"

int main(int argc,char *argv[])
{
	int rank, size, error_code;
	int arr[20], arr1[20], arr2[20];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0)
	{
		printf("Enter 16 elements\n");
		for(int i=0; i<16; i++)
			scanf("%d", &arr[i]);
	}

	error_code = MPI_Scatter(arr,4,MPI_INT,arr1,4,MPI_INT,0,MPI_COMM_WORLD);
	ErrorHandler(error_code);
	MPI_Scan(arr1, arr2, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	for(int i=0; i<4; i++)
		printf("%d ", arr2[i]);
	printf("\n");

	MPI_Finalize();
	return 0;
}