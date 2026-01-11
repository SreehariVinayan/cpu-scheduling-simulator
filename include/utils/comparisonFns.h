#ifndef COMPARE_FUNCTIONS
#define COMPARE_FUNCTIONS

#include "core/structs.h"

int compare_on_reamining_burst(const Process *a, const Process *b)
{
    if (a->remaining_burst_time != b->remaining_burst_time)
        return a->remaining_burst_time - b->remaining_burst_time;
    return a->arrival_time - b->arrival_time;
}

int compare_on_priority_value(const Process *a, const Process *b)
{
    if (a->priority != b->priority)
        return -a->priority + b->priority;
    return -a->arrival_time + b->arrival_time;
}

#endif