#include <stdio.h>
#include <mpi.h>

int main() {
	int np,pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int send[4];
	int recv;
	int result[4];

	if (pid == 0) {
		int num[4] = { 1,2,3,4 };
		for (int i = 0; i < 4; i++) {
			send[i] = num[i];
		}
	}
	MPI_Scatter(&send, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("process %d the received value is: %d\n", pid, recv);
	int square = recv * recv;
	MPI_Gather(&square, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (pid == 0) {
		printf("The square values:\n");
		for (int i = 0; i < 4; i++) {
			printf("%d,", result[i]);
		}
	}


	
	MPI_Finalize();
	return 0;
}