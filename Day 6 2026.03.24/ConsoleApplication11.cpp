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
        int arr[5] = { 1,2,3,4,5 };
        MPI_Send(&arr[2], 3, MPI_INT, 1, 50, MPI_COMM_WORLD);
    }

    if (pid == 1)
    {
        int recv[3];
        MPI_Recv(&recv, 3, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
        for (int i = 0; i < 3; i++)
        {
            printf("Received value: %d\n", recv[i]);
        }
    }

    MPI_Finalize();
    return 0;
}