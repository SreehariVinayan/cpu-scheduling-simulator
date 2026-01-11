#ifndef SORTAT_H
#define SORTAT_H

#include "structs.h"

// Comparison function for quick sort
int compare_process_function(const void *a, const void *b)
{
    return ((Process *)a)->arrival_time - ((Process *)b)->arrival_time;
}

// Sorting Processes with arrival time
void sort_process_list_on_arrival_time(int number_of_processes, Process *process_list)
{
    qsort(process_list, number_of_processes, sizeof(Process), compare_process_function);
};

#endif