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
	int sendbuf[4];
	int recvbuf;

	if (pid == 0)
	{
		sendbuf[0] = { 10 };
		sendbuf[1] = { 20 };
		sendbuf[2] = { 30 };
		sendbuf[3] = { 40 };
	}

	MPI_Scatter(sendbuf, 1, MPI_INT,&recvbuf,1,MPI_INT, 0, MPI_COMM_WORLD);
	printf("Process %d received %d\n", pid, recvbuf);

	MPI_Finalize();
	return 0;
}