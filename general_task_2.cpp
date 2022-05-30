#include <stdio.h>
#include "mpi.h"
#include <cstdlib>
#include <ctime>

void general_task_two(int* argc, char** argv)
{
    MPI_Init(argc, &argv);

    int rank, numtasks;

    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::srand(std::time(nullptr));

    int matrix[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = std::rand();
        }
    }

    

    MPI_Finalize();
}