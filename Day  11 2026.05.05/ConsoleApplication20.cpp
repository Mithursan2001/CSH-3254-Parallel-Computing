#include <stdio.h>
#include <mpi.h>

int main()
{
    int np, pid;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    MPI_Status sta;
    int num;
    int arr[4];
    num = pid * 10;

    MPI_Gather(&num, 1, MPI_INT,
                &arr, 1, MPI_INT,
                0, MPI_COMM_WORLD);

    if (pid == 0) {
        for (int i = 0; i < 4; i++)
        {
            printf("%d, ", arr[i]);
        }
    }

    MPI_Finalize();
    return 0;
}