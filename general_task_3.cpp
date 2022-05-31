#include <stdio.h>
#include "mpi.h"
#include <cstdlib>
#include <ctime>

void general_task_three(int* argc, char** argv)
{
	int size, rank;
	int num = 0;

	MPI_Init(argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("Process %d of %d\n", rank, size);

	num = rank;

	printf("Process %d, number %d\n", rank, num);

	int* buffer = (int*)calloc(size, sizeof(int));

	MPI_Allgather(&num, 1, MPI_INT, buffer, 1, MPI_INT, MPI_COMM_WORLD);

	printf("Process %d collected all numbers", rank);

	printf("\nbuffer:");

	for (int i = 0; i < size; i++)
	{
		printf("%d ", buffer[i]);
	}

	MPI_Finalize();
}
