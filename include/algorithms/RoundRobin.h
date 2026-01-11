#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include "core/structs.h"
#include "core/queue.h"

#include "utils/log_queue.h"
#include "utils/gantt.h"

// Round Robin simulation
void simulate_RR(int number_of_processes, Process *process_list, int time_quantum, int hide_gantt_chart)
{
    Process_Log *log_queue_head = NULL;

    Process_Queue *queue = (Process_Queue *)malloc(sizeof(Process_Queue));
    Process *ready_queue = (Process *)malloc(sizeof(Process) * number_of_processes);
    queue->maxSize = number_of_processes;
    queue->ready_queue = ready_queue;
    queue->front = -1;
    queue->rear = -1;

    Process dequeued_process;

    int current_time = 0;
    int finished_process_count = 0;
    int start_time = 0;
    int quantum_timer = 0;
    while (finished_process_count != number_of_processes)
    {
        if (queue->front != -1 && current_time != 0)
        {
            ready_queue[queue->front].remaining_burst_time--;
            if (quantum_timer == time_quantum)
            {
                dequeued_process = dequeue_process(queue);
                enqueue_process_log(&log_queue_head, dequeued_process.pid, start_time, current_time);
                start_time = current_time;
                enqueue_process(queue, dequeued_process);
                quantum_timer = 0;
            }
        }
        for (int i = 0; i < number_of_processes; i++)
        {
            if (process_list[i].arrival_time == current_time)
            {
                enqueue_process(queue, process_list[i]);
            }
        }
        if (ready_queue[queue->front].remaining_burst_time == 0)
        {
            finished_process_count++;
            dequeued_process = dequeue_process(queue);
            enqueue_process_log(&log_queue_head, dequeued_process.pid, start_time, current_time);
            start_time = current_time;
            for (int i = 0; i < number_of_processes; i++)
            {
                if (process_list[i].pid == dequeued_process.pid)
                {
                    process_list[i].waiting_time = current_time - dequeued_process.arrival_time - dequeued_process.burst_time;
                    quantum_timer = 0;
                    break;
                }
            }
        }
        current_time++;
        quantum_timer++;
    };

    free(ready_queue);
    free(queue);

    if (hide_gantt_chart == 0)
        print_gantt_chart(log_queue_head);

    free_memory(log_queue_head);
}

#endif