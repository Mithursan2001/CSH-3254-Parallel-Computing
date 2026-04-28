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
		int send_msg1[6] = { 20,30,40,50,50,60 };
		int send_msg2[6] = { 10,40,10,30,60,30 };
		int send_msg3[6] = { 40,20,30,10,50,30 };
		int send_msg4[6] = { 10,50,20,40,50,60 };

		MPI_Send(&send_msg1, 6, MPI_INT, 1, 50, MPI_COMM_WORLD);
		MPI_Send(&send_msg2, 6, MPI_INT, 2, 50, MPI_COMM_WORLD);
		MPI_Send(&send_msg3, 6, MPI_INT, 3, 50, MPI_COMM_WORLD);
		MPI_Send(&send_msg4, 6, MPI_INT, 4, 50, MPI_COMM_WORLD);
	}

	if (pid == 1) {

		int rec_msg1[6];
		int sum = 0;

		MPI_Recv(&rec_msg1, 6, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		for (int i = 0; i < 6; i++) {
			sum += rec_msg1[i];
		}

		MPI_Send(&sum, 1, MPI_INT, 0, 60, MPI_COMM_WORLD);

	}

	if (pid == 2) {

		int rec_msg2[6];

		int sum = 0;

		MPI_Recv(&rec_msg2, 6, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		for (int i = 0; i < 6; i++) {
			sum += rec_msg2[i];
		}

		MPI_Send(&sum, 1, MPI_INT, 0, 90, MPI_COMM_WORLD);

	}

	if (pid == 3) {

		int rec_msg3[6];

		int sum = 0;

		MPI_Recv(&rec_msg3, 6, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		for (int i = 0; i < 6; i++) {
			sum += rec_msg3[i];
		}

		MPI_Send(&sum, 1, MPI_INT, 0, 80, MPI_COMM_WORLD);

	}

	if (pid == 4) {

		int rec_msg4[6];
		int sum = 0;

		MPI_Recv(&rec_msg4, 6, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		for (int i = 0; i < 6; i++) {
			sum += rec_msg4[i];
		}

		MPI_Send(&sum, 1, MPI_INT, 0, 70, MPI_COMM_WORLD);

	}

	MPI_Finalize();
	return 0;

}
