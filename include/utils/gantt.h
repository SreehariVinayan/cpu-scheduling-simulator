#ifndef GANTT_H
#define GANTT_H

#include "core/structs.h"

void free_memory(Process_Log *process_execution_log_head)
{
    while (process_execution_log_head != NULL)
    {
        Process_Log *temp = process_execution_log_head;
        process_execution_log_head = process_execution_log_head->next_process;
        free(temp);
    }
}

void print_gantt_chart(Process_Log *process_execution_log_head)
{
    if (process_execution_log_head == NULL)
    {
        printf("\n\tCannot draw Gantt chart as Log HEAD pointer is NULL\n");
        return;
    }

    printf("\n\n\tGantt Chart:");

    int count = 0;
    Process_Log *curr = process_execution_log_head;

    int duration = 0;
    int length = 0;

    while (curr != NULL)
    {
        count++;
        duration = curr->finish_time - curr->start_time;
        length += (duration < 2) ? 2 : duration;
        curr = curr->next_process;
    }

    length += 3 * count + 1;

    // Top horizontal Bar
    printf("\n\t");
    for (int i = 0; i < length; i++)
    {
        printf("-");
    }
    printf("\n");

    // Gantt chart contents
    printf("\t|");

    curr = process_execution_log_head;
    while (curr != NULL)
    {
        duration = curr->finish_time - curr->start_time;
        if (duration < 2)
            duration = 2;

        for (int i = 0; i < duration / 2; i++)
        {
            printf(" ");
        }
        printf("P%d", curr->pid);
        for (int i = 0; i < duration - duration / 2; i++)
        {
            printf(" ");
        }
        printf("|");
        curr = curr->next_process;
    }

    // Bottom horizontal Bar
    printf("\n\t");
    for (int i = 0; i < length; i++)
    {
        printf("-");
    }
    printf("\n\t");

    // Time marking
    curr = process_execution_log_head;
    int digits_of_last_time_log = 1;
    while (1)
    {
        printf("%d", curr->start_time);
        duration = curr->finish_time - curr->start_time;
        duration = duration > 2 ? duration : 2;
        for (int i = 0; i < duration + 2 - digits_of_last_time_log + 1; i++)
            printf(" ");
        if (curr->next_process == NULL)
        {
            printf("%d", curr->finish_time);
            break;
        }
        curr = curr->next_process;
        digits_of_last_time_log = (curr->start_time == 0) ? 1 : (int)log10(curr->start_time) + 1;
    }
    printf("\n\n");
}

#endif