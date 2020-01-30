#include "mpi.h"
#include <stdio.h>
int main(int argc,char *argv[]){
	int rank,size,no,i,j,a[3][3],ele,sum;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0){
		printf("Enter values\n");
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				scanf("%d",&a[i][j]);

		printf("Enter element: ");
		scanf("%d",&ele);

	}
	MPI_Bcast(&ele,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(a,9,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0;i<3;i++)
	if(a[rank][i]==ele){
		no=no+1;
	}
		
	MPI_Reduce(&no,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0)
		printf("Occurences : %d ",sum);
	MPI_Finalize();
	return 0;
}