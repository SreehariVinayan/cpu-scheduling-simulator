#ifndef UTILS_H
#define UTILS_H

#include "core/structs.h"

void print_process_waiting_time(int number_of_processes, Process *process_list)
{
    printf("\n\tPID\t|\tWaiting Time");

    for (int i = 0; i < number_of_processes; i++)
    {
        printf("\n\tP%d\t|\t%d", process_list[i].pid, process_list[i].waiting_time);
    }
}

void print_process_list(int number_of_processes, Process *process_list)
{
    printf("\nPID\t|\tBurst Time\t|\tArrival Time \u2191\t|\tPriority");

    for (int i = 0; i < number_of_processes; i++)
    {
        printf("\nP%d\t|\t%d\t\t|\t%d\t\t|\t%d",
               process_list[i].pid,
               process_list[i].burst_time,
               process_list[i].arrival_time,
               process_list[i].priority);
    }

    printf("\n");
}

// Average Waiting Time Calculator
double get_avg_waiting_time(int number_of_processes, Process *process_list)
{
    int sum = 0;
    for (int i = 0; i < number_of_processes; i++)
    {
        sum += process_list[i].waiting_time;
    }
    return (double)sum / number_of_processes;
};

void print_waiting_time_table_header(Process *process_list, int number_of_processes)
{
    printf("\n\n\tWaiting Time Table\n\n\t");
    for (int i = 0; i < 16 * number_of_processes + 9; i++)
    {
        printf("-");
    }

    printf("\n\tPID");
    for (int i = 0; i < number_of_processes; i++)
    {
        printf("\t|\tP%d", process_list[i].pid);
    }
    printf("\t|\t\n\t");
    for (int i = 0; i < 16 * number_of_processes + 9; i++)
    {
        printf("-");
    }
    printf("\n");
}

void print_waiting_time_table_row(char *tag, Process *process_list, int number_of_processes)
{
    printf("\t%s", tag);
    for (int i = 0; i < number_of_processes; i++)
    {
        printf("\t|\t%d", process_list[i].waiting_time);
    }
    printf("\t|\t\n\t");
    for (int i = 0; i < 16 * number_of_processes + 9; i++)
    {
        printf("-");
    }
    printf("\n");
}

// For finding the minimum value of avg waiting times
void print_min_scheduler(
    float fcfs,
    float priority,
    float srtf,
    float rr)
{
    SchedulerResult schedulers[] = {
        {"FCFS", fcfs},
        {"SRTF", srtf},
        {"Non-preemptive Priority", priority},
        {"Round Robin", rr}};

    int n = sizeof(schedulers) / sizeof(schedulers[0]);
    int min_index = 0;

    for (int i = 1; i < n; i++)
    {
        if (schedulers[i].avg_waiting_time <
            schedulers[min_index].avg_waiting_time)
        {
            min_index = i;
        }
    }

    printf(
        "\n\tShortest Average Waiting Time: %s (%.2f ms)\n",
        schedulers[min_index].name,
        schedulers[min_index].avg_waiting_time);
}

void error(const char *msg)
{
    fprintf(stderr, "\nError: %s\n", msg);
    printf("\nUsage: ./a.out -<Number_Of_Processes> -{<PID>,<Burst_Time>,<Arrival_Time>,<Priority>}{...}...}\n\n");
    exit(EXIT_FAILURE);
}

#endif