#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int remaining_burst_time;
    int waiting_time;
    int is_not_null;
} Process;

typedef struct Process_Log
{
    int pid;
    int start_time;
    int finish_time;
    struct Process_Log *next_process;
} Process_Log;

typedef struct Process_Queue
{
    int front;
    int rear;
    int maxSize;
    Process *ready_queue;
} Process_Queue;

typedef struct
{
    const char *name;
    float avg_waiting_time;
} SchedulerResult;

typedef int (*ProcessCompare)(const Process *, const Process *);

#endif