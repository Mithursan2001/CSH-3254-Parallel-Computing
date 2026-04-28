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
		int Send_Num = 50;
		int Recv_Num;
		MPI_Send(&Send_Num, 1, MPI_INT, pid+1, 50, MPI_COMM_WORLD);
		printf("Mp processor id is %d and I'm sender the message is %d. \n", pid, Send_Num);

		MPI_Recv(&Recv_Num, 1, MPI_INT, np - 1, 50, MPI_COMM_WORLD, &sta);
		printf("Mp processor id is %d and I'm receiver the message is %d. \n", pid, Recv_Num);
	}

	else {
		int Recv_Num;
		MPI_Recv(&Recv_Num, 1, MPI_INT, pid-1, 50, MPI_COMM_WORLD, &sta);
		printf("Mp processor id is %d and I'm the receiver. Message is  %d. \n", pid, Recv_Num);

		if (pid == np - 1)
		{
			MPI_Send(&Recv_Num, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
		}
		else
		{
			MPI_Send(&Recv_Num, 1, MPI_INT, pid + 1, 50, MPI_COMM_WORLD);
		}
	}	

	MPI_Finalize();
	return 0;
}

/* Z:\2021ASP32\3. Third Year\2nd semester\CSC 3254\ConsoleApplication7\x64\Debug>mpiexec -n 4 ConsoleApplication7.exe
Mp processor id is 0 and I'm the sender to pid 50.
Mp processor id is 0 and I'm the receiver to pid 50.
Mp processor id is 2 and I'm the receiver. Message is  50.
Mp processor id is 1 and I'm the receiver. Message is  50.
Mp processor id is 3 and I'm the receiver. Message is  50. */