#include<stdio.h>
#include<mpi.h>
int main() {
	int np, pid;
	int A[4][4];
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	if (pid == 0) {
		int tempA[4][4] = {
			{2, 5, 8, 11},
			{14, 17, 20, 23},
			{26, 29, 32, 35},
			{38, 41, 44,47}};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				A[i][j] = tempA[i][j];
			}
		}
	}
	int recvA[4];
	MPI_Scatter(&A, 4, MPI_INT, &recvA, 4, MPI_INT, 0, MPI_COMM_WORLD);

	int even = 0;
	for (int i = 0; i < 4; i++) {
		if (recvA[i] % 2 == 0) {
			even++;
		}
	}
	int lcount[4];
	MPI_Gather(&even, 1, MPI_INT, &lcount, 1, MPI_INT, 0, MPI_COMM_WORLD);
	int teven;
	MPI_Reduce(&even, &teven, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (pid == 0) {
		printf("\nLocal even counts :\n ");
		for (int i = 0; i < 4; i++) {
			printf("%d ", lcount[i]);
		}
		printf("\nTotal even count  :%d ",teven);
	}
	MPI_Finalize();
	return 0;
}