#ifndef LOG_QUEUE
#define LOG_QUEUE

#include "core/structs.h"

void enqueue_process_log(Process_Log **head, int pid, int start_time, int finish_time)
{
    Process_Log *log = (Process_Log *)malloc(sizeof(Process_Log));
    log->pid = pid;
    log->start_time = start_time;
    log->finish_time = finish_time;
    log->next_process = NULL;

    if (*head == NULL)
    {
        *head = log;
    }
    else
    {
        Process_Log **curr = head;
        while ((*curr)->next_process != NULL)
        {
            curr = &(*curr)->next_process;
        }
        (*curr)->next_process = log;
    }
}

#endif