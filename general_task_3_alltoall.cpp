#include <stdio.h>
#include "mpi.h"
#include <cstdlib>
#include <ctime>

void general_task_three_alltoall(int* argc, char** argv)
{
	int size, rank;

	MPI_Init(argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int* number = (int*)calloc(size, sizeof(int));

	printf("Process %d work with number ", rank);

	for (int i = 0; i < size; i++) {
		number[i] = rank * size+i*10;
		printf("%d ", number[i]);
	}

	printf("\n");

	int* buffer_receive = (int*)calloc(size, sizeof(int));

	MPI_Alltoall(number, 1, MPI_INT, buffer_receive, 1, MPI_INT, MPI_COMM_WORLD);

	printf("Process %d is collect number", rank);

	for (int i = 0; i < size; i++) printf("%d ", buffer_receive[i]);

	printf("\n");

	MPI_Finalize();


}