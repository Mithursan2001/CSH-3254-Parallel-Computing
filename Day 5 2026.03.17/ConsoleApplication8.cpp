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

	int next = (pid + 1) % np;
	int prev = (pid - 1 + np) % np;

	if (pid == 0)
	{
		int num = 50;
		MPI_Send(&num, 1, MPI_INT, next, 50, MPI_COMM_WORLD);
		printf("I'm master. My id is %d I send %d to id %d \n", pid, num, next);

		MPI_Recv(&num, 1, MPI_INT, prev, 50, MPI_COMM_WORLD, &sta);
		printf("I'm master. My id is %d I receive %d from id %d \n", pid, num, prev);
	}

	else {
		int num;
		MPI_Recv(&num, 1, MPI_INT, prev, 50, MPI_COMM_WORLD, &sta);
		printf("My id is % d I receive % d from id % d \n", pid, num, prev);

		MPI_Send(&num, 1, MPI_INT, next, 50, MPI_COMM_WORLD);
		printf("My id is % d I send % d to id % d \n", pid, num, next);
	}

	MPI_Finalize();
	return 0;
}

/* Z:\2021ASP32\3. Third Year\2nd semester\CSC 3254\ConsoleApplication8\x64\Debug>mpiexec -n 4 ConsoleApplication8.exe
My id is  1 I receive  50 from id  0
My id is  1 I send  50 to id  2
My id is  3 I receive  50 from id  2
My id is  3 I send  50 to id  0
My id is  2 I receive  50 from id  1
My id is  2 I send  50 to id  3
I'm master. My id is 0 I send 50 to id 1
I'm master. My id is 0 I receive 50 from id 3 */
