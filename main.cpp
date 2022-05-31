#include <stdio.h>
#include "mpi.h"
#include "general_task_1.h"
#include "general_task_2.h"
#include "general_task_2_v.h"
#include "general_task_3.h"
#include "general_task_3_alltoall.h"
#include "general_task_4.h"
#include "general_task_4_allreduce.h"
#include "general_task_4_reduce_scatter.h"
#include "ind_task.h"

int main(int* argc, char** argv)
{
    ind_task(argc, argv);
}