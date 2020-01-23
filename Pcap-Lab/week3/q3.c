#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int non_vowels(char str[50], int len) {
	int nvowels = 0;
	for(int i = 0; i < len; i++) {
		if(!(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')) {
			nvowels++;
		}
	}
	return nvowels;
}

int main(int argc,char *argv[]) {

	char str[50],temp[50];
	int arr[20],size,rank,div;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0) {
		printf("Enter string: ");
		scanf("%s", str);

		div= strlen(str)/size;
	}

	MPI_Bcast(&div, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Scatter(&str, div, MPI_CHAR, &temp, div, MPI_CHAR, 0, MPI_COMM_WORLD);

	int nvows = non_vowels(temp, div);

	MPI_Gather(&nvows, 1, MPI_INT, arr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		int vows= 0;

		for(int i = 0; i <size; i++) {
			vows+= arr[i];
		}

		printf("No. of non-vowels: %d\n", vows);
	}

	MPI_Finalize();

	return 0;


}
