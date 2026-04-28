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
        int A[64] = {2,4,6,8,1,3,5,7,
         1,3,5,7,2,4,6,8,
         9,11,13,15,2,4,6,8,
         10,12,14,16,1,3,5,7,
         5,7,9,11,3,6,8,2,
         6,8,10,12,4,7,9,3,
         13,15,17,19,5,8,10,4,
         14,16,18,20,6,9,11,5};

        int X[8] = { 1,2,3,4,5,6,7,8 };

        for (int i = 1; i < np; i++) {
            MPI_Send(&X, 64, MPI_INT, i, 50, MPI_COMM_WORLD);
        }

        for (int i = 0; i < 8; i++) {
            MPI_Send(&A[i * 8], 8, MPI_INT, i, 50, MPI_COMM_WORLD);
        }


    }


    MPI_Finalize();
    return 0;
}