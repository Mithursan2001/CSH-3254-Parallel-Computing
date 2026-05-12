#include <stdio.h>
#include <mpi.h>

int main() {
	int np, pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int send;
	int recv[4];
	send = pid * 2;

	MPI_Gather(&send, 1, MPI_INT, recv, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (pid == 0) {
		printf("values: ");
		for (int i = 0; i < 4; i++) {
			printf("%d, ", recv[i]);
		}
	}
	

	MPI_Finalize();
	return 0;
}