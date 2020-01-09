#include "mpi.h"
#include <stdio.h>
int main(int argc,char *argv[]){
	int rank,size,i,j,flag;
	int low2=51,high2=100;
	int low=1,high=50;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0){
		    while (low < high) {
        flag = 0;
        // if low is a non-prime number, flag will be 1
        for (i = 2; i <= low / 2; ++i) {
            if (low % i == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            printf("%d ", low);
        ++low;
    }
		}

	if(rank==1){
		    while (low2 < high2) {
        flag = 0;
        // if low is a non-prime number, flag will be 1
        for (i = 2; i <= low2 / 2; ++i) {
            if (low2 % i == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            printf("%d ", low2);
        ++low2;
    }
		}

	MPI_Finalize();
	return 0;
}