#include <stdio.h>
#include <mpi.h>

int main() {
	int np, pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int send_arr[32];
	int recv_arr[8];

	if (pid == 0) {
		for (int i = 0; i < 32; i++) {
			send_arr[i] = i + 1;
		}

	}

	MPI_Scatter(send_arr, 8, MPI_INT, recv_arr, 8, MPI_INT, 0, MPI_COMM_WORLD);

	printf("Pid %d values: ", pid);
	int localsum=0;
	for (int i = 0; i < 8; i++) {
		printf("%d ", recv_arr[i]);
		localsum += recv_arr[i];
	}
	printf("\nPid %d sum: %d",pid,localsum);

	int finalsum[4];
	MPI_Gather(&localsum, 1, MPI_INT, finalsum, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (pid == 0) {
		int totalsum = 0;
		for (int i = 0; i < 4; i++) {
			totalsum = totalsum + finalsum[i];
		}
		printf("\nTotal sum: %d", totalsum);
	}
	

	MPI_Finalize();
	return 0;
}