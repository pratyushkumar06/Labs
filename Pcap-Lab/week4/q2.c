#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include "ErrorHandler.h"

int main(int argc,char *argv[])
{
	int rank, size, n, error_code;
	double pi, pi2, h, x, sum;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank == 0)
	{
		printf("Enter intervals : ");
		scanf("%d", &n);
	}

	error_code = MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	ErrorHandler(error_code);

	h = 1.0/(double)n;
	sum = 0.0;
	for(int i = rank+1; i<=n; i+=size)
	{
		x = h*((double)i - 0.5);
		sum = sum + 4.0/(1.0 + x*x);
	}
	pi2 = h*sum;
	MPI_Reduce(&pi2, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0)
		printf("Approx value of pi is : %f\n", pi);
	MPI_Finalize();
	return 0;
}