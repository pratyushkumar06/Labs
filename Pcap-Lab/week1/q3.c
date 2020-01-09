#include "mpi.h"
#include <stdio.h>
int main(int argc,char *argv[]){
	int rank,size,a,b,c;
	MPI_Init(&argc,&argv);
	//printf("Enter the Values\n");
	//scanf("%d %d",&a,&b);
	a=5;
	b=5;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0){
		printf("Performing Addition\n");
		c=a+b;
		printf("%d + %d = %d \n",a,b,c);
	}
	else if(rank==1){
		printf("Performing Division\n");
		c=(a/b);
		printf("%d / %d = %d\n",a,b,c );
	}
	else if(rank==2){
		printf("Performing Multiplication\n");
		c=a*b;
		printf("%d * %d = %d \n",a,b,c );
	}
	else if(rank==3){
		printf("Performing Subtraction\n");
		c=a-b;
		printf("%d - %d = %d \n",a,b,c );
	}
	//sprintf("My rank is %d in total %d process ",rank,size ); 
	MPI_Finalize();
	return 0;
}