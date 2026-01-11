#ifndef PRIORITY_H
#define PRIORITY_H

#include "core/structs.h"
#include "core/heap.h"
#include "utils/log_queue.h"
#include "utils/gantt.h"

// Preemptive Priority simulation
void simulate_Priority(int number_of_processes, Process *process_list, int hide_gantt_chart)
{
    Process_Log *process_log_head = NULL;
    Process_Heap *process_heap = createHeap(number_of_processes * 3, 2);

    int current_time = 1, start_time = 0;
    int finished_process_count = 0;

    for (int i = 0; i < number_of_processes; i++)
    {
        if (process_list[i].arrival_time == 0 && process_list[i].remaining_burst_time != 0)
            insertHeap(process_heap, process_list[i]);
    }

    Process curr_process = extractMin(process_heap);

    while (finished_process_count != number_of_processes)
    {
        curr_process.remaining_burst_time--;
        for (int i = 0; i < number_of_processes; i++)
        {
            if (curr_process.pid == process_list[i].pid)
            {
                if (curr_process.remaining_burst_time == 0)
                {
                    finished_process_count++;
                    process_list[i].waiting_time = current_time - curr_process.arrival_time - curr_process.burst_time;
                    enqueue_process_log(&process_log_head, curr_process.pid, start_time, current_time);
                    curr_process = extractMin(process_heap);
                    start_time = current_time;
                }
            }
            else if (process_list[i].arrival_time == current_time)
                insertHeap(process_heap, process_list[i]);
        }
        current_time++;
    }

    if (hide_gantt_chart == 0)
        print_gantt_chart(process_log_head);

    free(process_heap->processes);
    free(process_heap);

    free_memory(process_log_head);
}

#endif