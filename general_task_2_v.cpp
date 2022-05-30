#include <stdio.h>
#include "mpi.h"
#include <cstdlib>
#include <ctime>

void general_task_two_v(int* argc, char** argv)
{
    MPI_Init(argc, &argv);

    int rank, numtasks;

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::srand(std::time(nullptr));

    int matrix[4][4];

    if (rank == 0)
    {

        printf("Generated matrix:\n");

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrix[i][j] = std::rand();
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    int* buffer = (int*)malloc(sizeof(int) * 4);

    const int sendcounts[] = {4, 4, 4, 4};
    const int recvcounts[] = {1, 1, 1, 1};
    const int displs[] = {0, 4, 8, 12};
    const int displs1[] = {0, 1, 2, 3};
    

    // MPI_Scatter(matrix, 4, MPI_INT, buffer, 4, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatterv(matrix, sendcounts, displs, MPI_INT, buffer, 16, MPI_INT, 0, MPI_COMM_WORLD);

    int raw_sum = buffer[0] + buffer[1] + buffer[2] + buffer[3];

    int* raw_sums = NULL;

    if (rank == 0)
    {
        raw_sums = (int*)malloc(sizeof(int) * 4);
    }

    // MPI_Gather(&raw_sum, 1, MPI_INT, raw_sums, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gatherv(&raw_sum, 1, MPI_INT, raw_sums, recvcounts, displs1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Total sums:\n");

        for (int i = 0; i < 4; i++)
        {
            printf("%d ", raw_sums[i]);
        }
    }

    MPI_Finalize();
}