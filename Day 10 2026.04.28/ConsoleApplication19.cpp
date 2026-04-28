#include <stdio.h>
#include <mpi.h>

int main()
{
    int np, pid;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    int A[8][8], X[8], Y[8];
    int recvrow[8];
    int local_result = 0;

    if (pid == 0)
    {
        int tempA[8][8] = {
            {2,4,6,8,1,3,5,7},
            {1,3,5,7,2,4,6,8},
            {9,11,13,15,2,4,6,8},
            {10,12,14,16,1,3,5,7},
            {5,7,9,11,3,6,8,2},
            {6,8,10,12,4,7,9,3},
            {13,15,17,19,5,8,10,4},
            {14,16,18,20,6,9,11,5}
        };

        int tempX[8] = { 1,2,3,4,5,6,7,8 };

        for (int i = 0; i < 8; i++)
        {
            X[i] = tempX[i];
            for (int j = 0; j < 8; j++)
                A[i][j] = tempA[i][j];
        }
    }

    MPI_Bcast(X, 8, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(A, 8, MPI_INT, recvrow, 8, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received row: ", pid);
    for (int i = 0; i < 8; i++)
        printf("%d ", recvrow[i]);
    printf("\n");

    for (int i = 0; i < 8; i++)
        local_result += recvrow[i] * X[i];

    printf("Process %d partial result: %d\n", pid, local_result);

    if (pid == 0)
    {
        Y[0] = local_result;
        for (int i = 1; i < np; i++)
        {
            MPI_Recv(&Y[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("Final result vector Y:\n");
        for (int i = 0; i < 8; i++)
            printf("%d ", Y[i]);
        printf("\n");
    }
    else
    {
        MPI_Send(&local_result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}