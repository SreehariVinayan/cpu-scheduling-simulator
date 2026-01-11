#ifndef SRTF_H
#define SRTF_H

#include "core/structs.h"
#include "core/heap.h"
#include "utils/log_queue.h"
#include "utils/gantt.h"

// SRTF simulation
void simulate_SRTF(int number_of_processes, Process *process_list, int hide_gantt_chart)
{
    Process_Log *process_log_head = NULL;
    Process_Heap *process_heap = createHeap(number_of_processes * 3, 1);

    int current_time = 0;
    int finished_process_count = 0;

    int prev_process_pid = -1, start_time = 0;
    while (1)
    {
        for (int i = 0; i < number_of_processes; i++)
        {
            if (process_list[i].arrival_time == current_time)
                insertHeap(process_heap, process_list[i]);
        }
        if (!isHeapEmpty(process_heap))
        {
            Process extraced = extractMin(process_heap);
            while (extraced.remaining_burst_time == 0)
            {
                for (int i = 0; i < number_of_processes; i++)
                {
                    if (process_list[i].pid == extraced.pid)
                    {
                        process_list[i].waiting_time = current_time - extraced.arrival_time - extraced.burst_time;
                        break;
                    }
                }
                finished_process_count++;
                extraced = extractMin(process_heap);
                if (extraced.is_not_null == 0)
                    break;
            }
            if (finished_process_count == number_of_processes)
            {
                enqueue_process_log(&process_log_head, prev_process_pid, start_time, current_time);
                break;
            }
            if (prev_process_pid != -1 && prev_process_pid != extraced.pid)
            {
                enqueue_process_log(&process_log_head, prev_process_pid, start_time, current_time);
                start_time = current_time;
            }
            extraced.remaining_burst_time--;
            insertHeap(process_heap, extraced);
            prev_process_pid = extraced.pid;
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