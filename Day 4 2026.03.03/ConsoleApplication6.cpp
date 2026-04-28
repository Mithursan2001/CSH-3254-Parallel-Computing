#include <stdio.h>
#include <mpi.h>
#include <string.h>

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
		int Recv_Num[8];
		for (int i = 1; i < np; i++) {
			MPI_Recv(&Recv_Num[i], 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);
		}

		for (int i = 1; i < np; i++)
		{
			printf("Array Values: %d \n", Recv_Num[i]);
		}
	}
	else
	{
		int Send_Num = pid * 10;
		MPI_Send(&Send_Num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
		printf("Mp processor id is %d and I'm the sender to pid %d.\n",pid,Send_Num);
	}
	MPI_Finalize();
	return 0;
}