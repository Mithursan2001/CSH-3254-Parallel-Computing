#include<stdio.h>

#include<mpi.h>

int main()

{

	int np;

	int pid;

	MPI_Init(NULL, NULL);

	MPI_Comm_size(MPI_COMM_WORLD, &np);

	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	MPI_Status sta;

	if (pid == 0) {

		int send_msg[6] = { 20, 30, 40, 50, 50, 60 };

		for (int i = 1; i < 3; i++) {

			MPI_Send(&send_msg, 6, MPI_INT, i, 50, MPI_COMM_WORLD);

		}

		int global_sum = 0;

		for (int i = 1; i < 3; i++) {

			int recv_sum;

			MPI_Recv(&recv_sum, 1, MPI_INT, i, 60, MPI_COMM_WORLD, &sta);

			global_sum += recv_sum;

		}

		printf("Global sum = %d\n", global_sum);

	}

	if (pid == 1 || pid == 2) {

		int rec_msg[6];

		int sum = 0;

		MPI_Recv(&rec_msg, 6, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		for (int i = 0; i < 6; i++) {

			sum += rec_msg[i];

		}

		MPI_Send(&sum, 1, MPI_INT, 0, 60, MPI_COMM_WORLD);

	}

	MPI_Finalize();

	return 0;

}
