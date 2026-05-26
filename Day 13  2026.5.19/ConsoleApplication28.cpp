#include<stdio.h>
#include<mpi.h>

int main() {
	int np, pid;
	int A[4][4];

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	if (pid == 0) {
		int tempA[4][4] = { {10,4,7,12,},
					{6,25,9,15},
					{18,11,30,5},
					{14,8,16,22} };

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				A[i][j] = tempA[i][j];
			}
		}
	}
	int recv[4];
	MPI_Scatter(&A, 4, MPI_INT,
		&recv, 4, MPI_INT,
		0, MPI_COMM_WORLD);

	int primary = recv[pid];
	int secondary = recv[3 - pid];

	int maxPrimary;
	MPI_Reduce(&primary, &maxPrimary, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	int maxSecondary;
	MPI_Reduce(&secondary, &maxSecondary, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (pid == 0) {
		printf("\nMaximum primary diagonal element  :%d", maxPrimary);
		printf("\nMaximum primary diagonal element  :%d", maxSecondary);

	}
	
	MPI_Finalize();
	return 0;
}