#include<stdio.h>
#include<mpi.h>

int main() {
	int np, pid;
	int A[4][4];
	int B[4][4];

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	if (pid == 0) {
		int tempA[4][4] = {
			{25, 18, 12, 30},
			{14, 28, 20, 16},
			{35, 22, 10, 27},
			{19, 24, 32, 15}
		};

		int tempB[4][4] = {
			{5, 8, 2, 10},
			{4, 6, 12, 1},
			{15, 7, 3, 9},
			{8, 14, 11, 5}
		};

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				A[i][j] = tempA[i][j];
				B[i][j] = tempB[i][j];
			}
		}

	}
	int recvA[4];
	MPI_Scatter(&A, 4, MPI_INT, &recvA, 4, MPI_INT, 0, MPI_COMM_WORLD);

	int recvB[4];
	MPI_Scatter(&B, 4, MPI_INT, &recvB, 4, MPI_INT, 0, MPI_COMM_WORLD);

	int subtr[4];
	for (int i = 0; i < 4; i++) {
		subtr[i] = recvA[i] - recvB[i];
	}

	int C[4][4];
	MPI_Gather(&subtr, 4, MPI_INT, &C, 4, MPI_INT, 0, MPI_COMM_WORLD);
	
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum = sum + subtr[i];
	}

	int Total_sum = 0;
	MPI_Reduce(&sum, &Total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (pid == 0) {
		printf("\nFinal subtraction matrix : \n");
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				printf("%d ",C[i][j]);
			}
			printf("\n");
		}
		printf("\nTotal sum of elements  :%d ", Total_sum);
	}

	
	MPI_Finalize();
	return 0;

}