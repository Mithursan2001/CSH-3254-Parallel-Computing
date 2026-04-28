#include <mpi.h>
#include <stdio.h>
#include <string.h>
int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);//initialize the mpi kind of virtual environment
	MPI_Comm_size(MPI_COMM_WORLD, &np);//np-No of processing element
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);//assign unique processor id for each processor element

	MPI_Status sta;
	if (pid == 0)
	{
		int sum = 0;
		int Send_Num[5] = { 10,20,30,40,50 };
		MPI_Send(&Send_Num, 5, MPI_INT, 1, 50, MPI_COMM_WORLD);

		printf("My processor id is %d and I'm the sender.\n", pid);
		printf("Sum receive from pid1 \n:",pid);
	}
	if (pid == 1)
	{
		int Recv_msg[5];
		int sum = 0;

		MPI_Recv(&Recv_msg, 5, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		printf("My processor id is %d and I'm the receiver. \n", pid);
		printf("Received messages are,");
		for (int i = 0; i < 5; i++)
		{
			printf("%d \n", Recv_msg[i]);
		}
		printf("Sum of numbers are,");
		for (int i = 0; i < 5; i++)
		{
			sum = sum + Recv_msg[i];
		}
		printf("%d \n",sum);

		MPI_Send(&sum, 1, MPI_INT, 0, 30, MPI_COMM_WORLD);
		
	}
	MPI_Finalize();
	return 0;
}