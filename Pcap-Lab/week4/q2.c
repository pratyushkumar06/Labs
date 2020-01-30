#include "mpi.h"
#include <stdio.h>
int occur(int arr[20][20],int key){
	int i,j,occ;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(arr[i][j]==key){
				occ++;
			}
		}
		return occ;
}
int main(int argc,char *argv[]){
	int rank,size,fact=1,factsum,i,j,arr[20][20],ele,M=3,arr2[20][20];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(rank==0){
		printf("Enter array\n");
		for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			scanf("%d",&arr[i][j]);
		}
	}
		printf("Enter element\n");
		scanf("%d",&ele);
		M=3;
	}
	MPI_Bcast(&M , 1, MPI_INT, 0, MPI_COMM_WORLD);

	
		
	MPI_Scatter(&arr,M,MPI_INT,&arr2,M,MPI_INT,0,MPI_COMM_WORLD);
	int c=occur(arr,ele);
	MPI_Scan(&c,&factsum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	if(rank==size-1)
		printf("Sum is : %d ",factsum);

	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
	MPI_Finalize();
	return 0;
}