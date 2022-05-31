#include <stdio.h>
#include "mpi.h"
#include <cstdlib>
#include <ctime>

void general_task_four_reduce_scatter(int* argc, char** argv)
{
    MPI_Init(argc, &argv);

    int rank, size, result = 0;
    int array[100];

    for (int i = 0; i < 100; i++)
    {
        array[i] = i;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_min = 100;
    int local_max = 0;

    for (int i = rank * 100 / size; i < (rank + 1) * 100 / size; i++)
    {
        if (local_min > array[i])
        {
            local_min = array[i];
        }
    }

    for (int i = rank * 100 / size; i < (rank + 1) * 100 / size; i++)
    {
        if (local_max < array[i])
        {
            local_max = array[i];
        }
    }

    printf("Local min for process %d is %d\n", rank, local_min);
    printf("Local max for process %d is %d\n", rank, local_max);

    int min, max;

    const int recvcounts[] = { 1, 1, 1, 1 };

    // MPI_Reduce(&local_max, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    // MPI_Allreduce(&local_max, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

    // MPI_Reduce(&local_min, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    // MPI_Allreduce(&local_min, &min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

    MPI_Reduce_scatter(&local_min, &min, recvcounts, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Reduce_scatter(&local_max, &max, recvcounts, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Global min is %d\n", min);
        printf("Global max is %d\n", max);
    }

    MPI_Finalize();
}