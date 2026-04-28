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

	if (pid == 0) {
		int sequence1[32] = { 45, 41, 92, 79, 11, 83, 97, 91, 98, 67, 53, 34, 68, 72, 76, 12,
							78, 59, 64, 06, 89, 62, 26, 23, 17, 35, 36, 18, 25, 55, 43, 56 };
		int sequence2[32] = { 05, 18, 96, 63, 23, 10, 42, 34, 58, 84, 35, 61, 51, 41, 01, 13,
							45, 22, 53, 44, 56, 96, 62, 71, 67, 72, 78, 46, 83, 91, 97, 98 };

		for (int i = 1; i < np; i++) {
			MPI_Send(&sequence1, 32, MPI_INT, i, 50, MPI_COMM_WORLD);
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

		int master_ctn = 0;
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (sequence1[i] == sequence2[j])
				{
					master_ctn++;
					break;
				}
			}
		}

		int total_ctn = master_ctn, local_ctn;
		for (int i = 1; i < 4; i++)
		{
			MPI_Recv(&local_ctn, i, MPI_INT, 0, 57, MPI_COMM_WORLD, &sta);
			total_ctn = total_ctn + local_ctn;
		}

		float dice = (2.0 * total_ctn) / (32 + 32);

		printf("Dice Coefficient= %.3f\n", dice);
		printf("similarity= %.2f\n", dice * 100);
		printf("process %d intersection =%d\n", pid, total_ctn);

	}

	else {
		int recv_sequence1[32];
		MPI_Recv(&recv_sequence1, 32, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);

		int recv_sequence2[8];
		MPI_Recv(&recv_sequence2, 8, MPI_INT, 0, 55, MPI_COMM_WORLD, &sta);

		printf("process %d received: ", pid);
		for (int i = 0; i < 8; i++)
		{
			printf("%d ", recv_sequence2[i]);
			printf("\n");
		}

		int ctn = 0;
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (recv_sequence1[i] == recv_sequence2[j])
				{
					ctn++;
					break;
				}
			}
		}
		printf("process %d local intersection= %d\n",pid, ctn);
		MPI_Send(&ctn,1 , MPI_INT, 0, 57, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}