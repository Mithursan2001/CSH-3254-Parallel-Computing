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
		int num = pid;
		MPI_Send(&num, 1, MPI_INT, next, 50, MPI_COMM_WORLD);
		printf("I'm master. My id is %d I send %d to id %d \n", pid, num, next);

		int global_sum;
		MPI_Recv(&global_sum, 1, MPI_INT, prev, 50, MPI_COMM_WORLD, &sta);
		printf("I'm master. My id is %d I receive %d from id %d \n", pid, global_sum, prev);
	}

	else {
		int num;
		int local_sum;
		MPI_Recv(&num, 1, MPI_INT, prev, 50, MPI_COMM_WORLD, &sta);
		printf("My id is % d I receive % d from id % d \n", pid, num, prev);

		local_sum =num+ pid;

		MPI_Send(&local_sum, 1, MPI_INT, next, 50, MPI_COMM_WORLD);
		printf("My id is % d I send % d to id % d \n", pid, local_sum, next);
	}

	MPI_Finalize();
	return 0;
}


/* Z:\2021ASP32\3. Third Year\2nd semester\CSC 3254\ConsoleApplication9\x64\Debug>mpiexec -n 4 ConsoleApplication9.exe
My id is  1 I receive  0 from id  0
My id is  1 I send  1 to id  2
My id is  2 I receive  1 from id  1
My id is  2 I send  3 to id  3
I'm master. My id is 0 I send 0 to id 1
I'm master. My id is 0 I receive 6 from id 3
My id is  3 I receive  3 from id  2
My id is  3 I send  6 to id  0 */