#include <stdio.h>
#include <mpi.h>

int main()
{
    int np, pid;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    MPI_Status sta;
    int send_arr[8];
    int recv_arr[2];

    if (pid == 0)
    {
        int arr[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
        for (int i = 0; i < 8; i++)
        {
            send_arr[i] = arr[i];
        }
    }

    MPI_Scatter(&send_arr, 2, MPI_INT, recv_arr, 2, MPI_INT, 0, MPI_COMM_WORLD);
    
    int lsum = recv_arr[0] + recv_arr[1];
    printf("Process %d received: ", pid);
    for (int i = 0; i < 2; i++) {
        printf("%d ", recv_arr[i]);
    }

    int fsum[4];
    MPI_Gather(&lsum, 1, MPI_INT,
        &fsum, 1, MPI_INT,
        0, MPI_COMM_WORLD);

    printf("\n");
    if (pid == 0)
    {
        printf("Final Answer: ");
        for (int i = 0; i < 4; i++)
        {
            printf("%d ", fsum[i]);
        }
    }

    MPI_Finalize();
    return 0;
}