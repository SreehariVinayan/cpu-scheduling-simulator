#ifndef READY_QUEUE
#define READY_QUEUE

#include "structs.h"

// Enqueue Process to Ready queue
void enqueue_process(Process_Queue *queue, Process process)
{
    if (queue->rear == -1)
    {
        queue->front = 0;
    }
    else if ((queue->rear + 1) % queue->maxSize == queue->front)
    {
        return;
    }
    int index = (queue->rear + 1) % queue->maxSize;
    queue->ready_queue[index] = process;
    (queue->rear)++;
}

// Dequeue Process to Ready queue
Process dequeue_process(Process_Queue *queue)
{
    Process process = queue->ready_queue[queue->front];
    if (queue->front == -1)
        return process;
    else
    {
        (queue->front) = (queue->front + 1) % queue->maxSize;
        if (queue->front > queue->rear)
        {
            queue->front = -1;
            queue->rear = -1;
        }
    }
    return process;
}

void print_ready_queue(Process *ready_queue, int front, int rear)
{
    if (front == -1)
    {
        printf("\nEmpty");
        return;
    }
    for (int i = front; i < rear + 1; i++)
    {
        printf("P%d, ", ready_queue[i].pid);
    }
    printf("\n");
}

#endif