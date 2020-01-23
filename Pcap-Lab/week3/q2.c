#include "mpi.h"
#include <stdio.h>
float average(float arr[20], int n) {

	float avg = 0.0;
	for(int i = 0; i < n; i++) {
		avg += arr[i];
	}
	float x=avg / (float)n;
	return x;
}
int main(int argc,char *argv[]){
	int rank,size,N,c,i,M;
	float A[20],B[20],C[20];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(rank==0){
		printf("Enter the value of M\n");
	    scanf("%d",&M);
		N=size*M;
		fprintf(stdout, "Enter %d values\n",N );
		fflush(stdout);
		for(i=0;i<N;i++){
			scanf("%f",&A[i]);
		}
	}
	MPI_Bcast(&M , 1, MPI_INT, 0, MPI_COMM_WORLD);

	
		
	MPI_Scatter(&A,M,MPI_FLOAT,&C,M,MPI_FLOAT,0,MPI_COMM_WORLD);

	float avg = average(C, M);

	MPI_Gather(&avg, 1, MPI_FLOAT, B, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	if(rank==0){
		float aavg = average(B, size);
		printf("Average of gathered average is: %.2f\n", aavg);
		}
		MPI_Finalize();
		return 0;
}

