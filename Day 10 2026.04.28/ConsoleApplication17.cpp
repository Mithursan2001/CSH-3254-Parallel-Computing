#include <stdio.h>
#include <mpi.h>

int main()
{
	int np;
	int pid, data;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	MPI_Status sta;

	int num;
	int send_arr[5];

	if (pid == 0)
	{
		num = 5;
		send_arr[0] = 1;
		send_arr[1] = 2;
		send_arr[2] = 3;
		send_arr[3] = 4;
		send_arr[4] = 5;
	}

	MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Bcast(&send_arr, 5, MPI_INT, 0, MPI_COMM_WORLD);

	printf("Process ID: %d, Value Received: %d\n", pid, num);

	printf("Received Array Values: ");
	for (int i = 0; i < 5; i++)
	{
		printf(" %d, ", send_arr[i]);
	}
	printf("\n");

	MPI_Finalize();
	return 0;
}