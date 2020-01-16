#include "mpi.h"
#include <stdio.h>
int main(int argc,char *argv[]){
	int rank,size,x,i;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0){
		printf("Enter a value in master process\n");
		scanf("%d",&x);
		for(i=1;i<size;i++){
		MPI_Send(&x,5,MPI_INT,i,1,MPI_COMM_WORLD);
		fprintf(stdout,"I have send %d to process %d\n",x,i);
		fflush(stdout);
		}
		
	}
	else{
	
		MPI_Recv(&x,5,MPI_INT,i,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have received %d in process %d\n",x,i);
		fflush(stdout);

	}
	MPI_Finalize();
	return 0;
}