#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc,char *argv[]){
	int rank,size,n,i;
	char x[30],y[30];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0){
		printf("Enter a value in master process\n");
		gets(x);
		MPI_Ssend(&x,30,MPI_CHAR,1,1,MPI_COMM_WORLD);
		fprintf(stdout,"I have send %s from process 0\n",x);
		fflush(stdout);
		MPI_Recv(&y,30,MPI_CHAR,1,2,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have received %s in process 1 after Toggle\n",y);
		fflush(stdout);

	}
	else{
		MPI_Recv(&x,30,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		fprintf(stdout, "I have received %s in process 1\n",x );
		fflush(stdout);
		while(x[i]!='\0'){
			if(x[i]>='a' && x[i]<='z')
        {
            y[i] = x[i] - 32;
        }
        else if(x[i]>='A' && x[i]<='Z')
        {
            y[i] = x[i] + 32;
        }

        i++;
		}
		MPI_Ssend(&y,30,MPI_CHAR,0,2,MPI_COMM_WORLD);
		fprintf(stdout, "I have sent %s in process 0 after Toggle\n",y);
		fflush(stdout);
		
		
	}
	MPI_Finalize();
	return 0;
}