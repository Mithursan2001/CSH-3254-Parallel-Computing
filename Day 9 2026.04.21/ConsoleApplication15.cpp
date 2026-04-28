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

	if (pid == 0)
	{
		char msg[] = "I am from UOV";

		MPI_Send(&msg, sizeof(msg), MPI_CHAR, 1, 50, MPI_COMM_WORLD);
		printf("Master : %s\n", msg);
		
	}
	else
	{
		char recv_msg[100];
		MPI_Recv(&recv_msg, 100, MPI_CHAR, 0, 50, MPI_COMM_WORLD, &sta);
		printf("Received message : %s\n", recv_msg);
	}

	MPI_Finalize();
	return 0;
}