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
		MPI_Send(&x,5,MPI_INT,rank+1,1,MPI_COMM_WORLD);
		MPI_Recv(&x,5,MPI_INT,size-1,1,MPI_COMM_WORLD,&status);
		printf("Received Back val %d from process %d\n",x,size-1);
	}
	else{
 
		MPI_Recv(&x,5,MPI_INT,rank-1,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have received %d from process %d\n",x,rank-1);
		fflush(stdout);
		x++;
		MPI_Send(&x,5,MPI_INT,(rank+1)%size,1,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}