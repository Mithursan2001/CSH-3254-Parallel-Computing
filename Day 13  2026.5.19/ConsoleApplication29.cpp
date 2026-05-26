#include<stdio.h>
#include<mpi.h>
int main() {
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int A[4][4];

	if (pid == 0) {
		int tempA[4][4] = { {12,5,18,9},
							{ 27, 14, 3 ,20},
							{ 8,31,16,11},
							{25, 7, 22, 4 } };
							
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				A[i][j] = tempA[i][j];
			}
		}
	}
	int RA[4];
	MPI_Scatter(&A, 4, MPI_INT,
	            &RA,4,MPI_INT,
		         0,MPI_COMM_WORLD);

	//Selection Sorting
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			if (RA[i] > RA[j]) {
				int temp = RA[i];
				RA[i] = RA[j];
				RA[j] = temp;
			}	
		}
	}
	int B[4][4];

	MPI_Gather(&RA, 4, MPI_INT,
		&B, 4, MPI_INT,
		0, MPI_COMM_WORLD);

	int maxB[4];

	MPI_Reduce(&RA, &maxB, 4, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	
	if (pid == 0) {
		int max = maxB[0];
		for (int i = 1; i < 4; i++) {
			if (maxB[i] > max) {
				max = maxB[i];
			}
		}
		printf("Sorted matrix:\n");
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				printf("%d ", B[i][j]);
			}
			printf("\n");
			
		}
		printf("Maximum matrix element:%d\n ", max);
		
	}

	MPI_Finalize();
	return 0;
}