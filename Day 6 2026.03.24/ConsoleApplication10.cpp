#include <stdio.h>
#include <mpi.h>

int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	MPI_Status sta;

	if (pid == 0) {
		int numbers[6] = { 10,20,30,40,50,60 };	
		int value;
		int sum1, sum3;
		for (int i = 1; i <= 5; i++) {
			MPI_Send(&numbers[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		MPI_Recv(&sum1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &sta);
		MPI_Recv(&sum3, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, &sta);

		int total = numbers[0] + sum1 + sum3;
		printf("Final Total Sum = %d\n", total);

	}
	
	if (pid == 1) {
		int value;
		int sum;
		int recv_val;
		MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &sta);
		MPI_Recv(&recv_val, 1, MPI_INT, 2, 0, MPI_COMM_WORLD,&sta);
		sum = value + recv_val;
		MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	if (pid == 2) {
		int value;
		MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &sta);
		MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}

	if (pid == 3) {
		int value;
		int sum;
		int recv_val;
		MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &sta);
		MPI_Recv(&recv_val, 1, MPI_INT, 4, 0, MPI_COMM_WORLD, &sta);
		sum = value + recv_val;
		MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	if (pid == 4) {
		int value;
		int sum;
		int recv_val;
		MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &sta);
		MPI_Recv(&recv_val, 1, MPI_INT, 5, 0, MPI_COMM_WORLD, &sta);
		sum = value + recv_val;
		MPI_Send(&sum, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);

	}

	if (pid == 5) {
		int value;
		MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &sta);
		MPI_Send(&value, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;

}







