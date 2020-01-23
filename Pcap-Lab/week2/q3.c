#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main(int argc,char *argv[]){
	int rank,size,x,i,square,cube;
	MPI_Init(&argc,&argv);
	int arr[40];
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	int *buffer=(int *)malloc(100*sizeof(int)); 
	int bsize=100*sizeof(int);
	
	if(rank==0){
		printf("Enter array elements\n");
		for(i=0;i<size;i++)
			scanf("%d",&arr[i]);
		MPI_Buffer_attach(buffer,bsize);
		for(i=1;i<10;i++){
		MPI_Bsend(&arr[i],20,MPI_INT,i,i,MPI_COMM_WORLD);
		fprintf(stdout,"I have send %d to process %d\n",arr[i],i);
		fflush(stdout);
		}
		MPI_Buffer_detach(&buffer,&bsize);
	}
	else if(rank%2==0) {
		MPI_Recv(&arr[i], 20, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		square=arr[i]*arr[i];
		fprintf(stdout, "I have received %d and squared to %d\n",arr[i],square);
		fflush(stdout);

	} else {
		MPI_Recv(&arr[i], 20, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
		cube=arr[i]*arr[i]*arr[i];
		fprintf(stdout, "I have received %d and cubed to %d\n",arr[i],cube);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}