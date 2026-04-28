#include <stdio.h>
#include <mpi.h>
#include <iostream>

int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	MPI_Status sta;

	if (pid == 0) {
		int sequence1[32] = { 12, 25, 37, 44, 59, 63, 71, 82, 91, 10, 22, 35, 48, 50, 67, 73,
85, 90, 14, 18, 21, 27, 33, 39, 46, 52, 60, 66, 75, 88, 95, 99 };

		int sequence2[32] = { 11, 20, 35, 40, 55, 60, 70, 80, 90, 15, 25, 30, 45, 55, 65, 70,
80, 85, 10, 20, 22, 28, 30, 38, 48, 50, 62, 68, 72, 85, 90, 100 };

		
		for (int i = 1; i < 4; i++) {
			MPI_Send(&sequence1[i * 8], 8, MPI_INT, i, 55, MPI_COMM_WORLD);
		}
		
		for (int i = 1; i < 4; i++) {
			MPI_Send(&sequence2[i * 8], 8, MPI_INT, i, 55, MPI_COMM_WORLD);
		}
		printf("process %d received: ", pid);
		for (int i = 0; i < 8; i++)
		{
			printf("%d ", sequence2[i]);
			printf("\n");
		}

		int partial = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (sequence1[i] == sequence2[j])
				{
					partial++;
					break;
				}
			}
		}

		int partial_sum_A = 0;
		for (int i = 0; i < 32; i++)
		{
			partial_sum_A=partial_sum_A+(sequence1[i]* sequence1[i]);
		}

		int partial_sum_B = 0;
		for (int i = 0; i < 32; i++)
		{
			partial_sum_B = partial_sum_B + (sequence2[i] * sequence2[i]);
		}

		int total_partial = partial, local_sum;
		int total_sum_A = partial_sum_A;
		int total_sum_B = partial_sum_B;
		for (int i = 1; i < 4; i++)
		{
			MPI_Recv(&local_sum, i, MPI_INT, 0, 57, MPI_COMM_WORLD, &sta);
			total_partial = total_partial + local_sum;
			total_sum_A = partial_sum_A;
			total_sum_B = total_sum_B;
		}

		float cosine = (total_partial) / (sqrt(partial_sum_A)* sqrt(partial_sum_B));

		printf("Cosine Similarity= %.3f\n", cosine);

	}

	else {
		int recv_sequence1[8];
		MPI_Recv(&recv_sequence1, 8, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		int recv_sequence2[8];
		MPI_Recv(&recv_sequence2, 8, MPI_INT, 0, 55, MPI_COMM_WORLD, &sta);

		printf("process %d received: ", pid);
		for (int i = 0; i < 8; i++)
		{
			printf("%d ", recv_sequence2[i]);
			printf("\n");
		}

		int partial = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (recv_sequence1[i] == recv_sequence2[j])
				{
					partial++;
					break;
				}
			}
		}
		printf("process %d local intersection= %d\n", pid, partial);
		MPI_Send(&partial, 1, MPI_INT, 0, 57, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}