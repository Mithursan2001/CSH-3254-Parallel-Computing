#include <stdio.h>
#include <mpi.h>

int main()
{
    int np, pid;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    int sum = pid + 100;
    int result;

    MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (pid == 0) {
        printf("Result: %d", result);
    }
    MPI_Finalize();
    return 0;
}