#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <chrono>
#include <list>
#include <iostream>
#include <mpi.h>

void ind_task(int* argc, char** argv)
{
    MPI_Init(argc, &argv);

    int rank, size;

    const int ARR_SIZE = 100;

    float min, max;

    float results[ARR_SIZE];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < ARR_SIZE; i++)
    {
        results[i] = (i + 0.5) * (i + 0.5);
    }

    float local_min = results[0];
    float local_max = results[0];

    for (int i = rank * ARR_SIZE / size; i < (rank + 1) * ARR_SIZE / size; i++)
    {
        if (local_min > results[i])
        {
            local_min = results[i];
        }
    }

    for (int i = rank * ARR_SIZE / size; i < (rank + 1) * ARR_SIZE / size; i++)
    {
        if (local_max < results[i])
        {
            local_max = results[i];
        }
    }

    printf("Local min for process %f is %f\n", rank, local_min);
    printf("Local max for process %f is %f\n", rank, local_max);

    MPI_Reduce(&local_max, &max, 1, MPI_FLOAT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min, &min, 1, MPI_FLOAT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Global min is %f\n", min);
        printf("Global max is %f\n", max);
    }

    MPI_Finalize();
}