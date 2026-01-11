/*
    Input a list of processes, their CPU burst times (integral values), arrival times, and priorities.
    Then simulate FCFS, SRTF, non-preemptive priority (a larger priority number implies a higher priority), and
    RR (quantum = 3 units) scheduling algorithms on the process mix, determining which algorithm
    results in the minimum average waiting time (over all processes).
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "core/structs.h"
#include "core/sortAT.h"

#include "utils/utils.h"
#include "utils/gantt.h"

#include "algorithms/FCFS.h"
#include "algorithms/SRTF.h"
#include "algorithms/Priority.h"
#include "algorithms/RoundRobin.h"

#define SHOW_GANTT_CHART 0
#define HIDE_GANTT_CHART 1

int main()
{
    int number_of_processes = 5;
    int quantum = 3;
    Process *process_list = (Process *)malloc(sizeof(Process) * number_of_processes);

    // Refer structs.h for struct definition.
    // Number of processes should be equal to the variable "number_of_processes"
    // Process = {pid, burst_time, arrival_time, priority, remaining_burst_time, 0, 1}
    process_list[0] = (Process){1, 10, 0, 0, 10, 0, 1};
    process_list[1] = (Process){2, 5, 5, 1, 5, 0, 1};
    process_list[2] = (Process){3, 8, 7, 2, 8, 0, 1};
    process_list[3] = (Process){4, 2, 9, 3, 2, 0, 1};
    process_list[4] = (Process){5, 5, 9, 4, 5, 0, 1};

    // Scheduling algorithms do not depend on this sorting.
    // This is done for illustrative purposes only.
    sort_process_list_on_arrival_time(number_of_processes, process_list);

    printf("\nProcess List\n");
    printf("------------\n");

    print_process_list(number_of_processes, process_list);

    int choice = 0;
    double avg_waiting_time_FCFS = -1, avg_waiting_time_SRTF = -1;
    double avg_waiting_time_Priority = -1, avg_waiting_time_RR = -1;

    while (1)
    {
        choice = 0;

        printf("\nChoose Scheduling Algorithm: \n");
        printf("\n1. First-Come-First-Serve (FCFS)\n");
        printf("2. Shortest Remaining Time First (SRTF)\n");
        printf("3. Non-preemptive priority\n");
        printf("4. Round Robin (RR)\n");
        printf("5. Compare all scheduling algorithms\n");
        printf("6. Exit program.\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("\n\tFirst-Come-First-Serve Scheduling Algorithm (FCFS)\n");
            printf("\t-------------------------------------------\n");

            simulate_FCFS(number_of_processes, process_list, SHOW_GANTT_CHART);
            print_process_waiting_time(number_of_processes, process_list);
            avg_waiting_time_FCFS = get_avg_waiting_time(number_of_processes, process_list);

            printf("\n\n\tAverage waiting time = %.2f ms. \n\n", avg_waiting_time_FCFS);
        }
        else if (choice == 2)
        {
            printf("\n\tShortest Remaining Time First (SRTF)\n");
            printf("\t------------------------------------");

            simulate_SRTF(number_of_processes, process_list, SHOW_GANTT_CHART);
            print_process_waiting_time(number_of_processes, process_list);
            avg_waiting_time_SRTF = get_avg_waiting_time(number_of_processes, process_list);

            printf("\n\n\tAverage waiting time = %.2f ms. \n\n", avg_waiting_time_SRTF);
        }
        else if (choice == 3)
        {
            printf("\n\tNon-preemptive priority\n");
            printf("\t-----------------------");

            simulate_Priority(number_of_processes, process_list, SHOW_GANTT_CHART);
            print_process_waiting_time(number_of_processes, process_list);
            avg_waiting_time_Priority = get_avg_waiting_time(number_of_processes, process_list);

            printf("\n\n\tAverage waiting time = %.2f ms. \n\n", avg_waiting_time_Priority);
        }
        else if (choice == 4)
        {
            printf("\n\tRound Robin\n");
            printf("\t-----------");
            printf("\nEnter quantum value = ");
            scanf("%d", &quantum);

            simulate_RR(number_of_processes, process_list, quantum, SHOW_GANTT_CHART);
            print_process_waiting_time(number_of_processes, process_list);
            avg_waiting_time_RR = get_avg_waiting_time(number_of_processes, process_list);

            printf("\n\n\tAverage waiting time = %.2f ms. \n\n", avg_waiting_time_RR);
        }
        else if (choice == 5)
        {
            printf("\n\tComparision of FCFS, SRTF, Priority and RR\n");
            printf("\t------------------------------------------");

            print_waiting_time_table_header(process_list, number_of_processes);

            if (avg_waiting_time_FCFS == -1)
            {
                simulate_FCFS(number_of_processes, process_list, HIDE_GANTT_CHART);
                print_waiting_time_table_row("FCFS", process_list, number_of_processes);
                avg_waiting_time_FCFS = get_avg_waiting_time(number_of_processes, process_list);
            }
            if (avg_waiting_time_SRTF == -1)
            {
                simulate_SRTF(number_of_processes, process_list, HIDE_GANTT_CHART);
                print_waiting_time_table_row("SRTF", process_list, number_of_processes);
                avg_waiting_time_SRTF = get_avg_waiting_time(number_of_processes, process_list);
            }
            if (avg_waiting_time_Priority == -1)
            {
                simulate_Priority(number_of_processes, process_list, HIDE_GANTT_CHART);
                print_waiting_time_table_row("PEP", process_list, number_of_processes);
                avg_waiting_time_Priority = get_avg_waiting_time(number_of_processes, process_list);
            }
            if (avg_waiting_time_RR == -1)
            {
                simulate_RR(number_of_processes, process_list, quantum, HIDE_GANTT_CHART);
                print_waiting_time_table_row("RR", process_list, number_of_processes);
                avg_waiting_time_RR = get_avg_waiting_time(number_of_processes, process_list);
            }

            printf("\n\n\tAverage Waiting Times\n\t");
            printf("\n\t- FCFS : %.2f ms", avg_waiting_time_FCFS);
            printf("\n\t- SRTF : %.2f ms", avg_waiting_time_SRTF);
            printf("\n\t- Non-preemptive Priority : %.2f ms", avg_waiting_time_Priority);
            printf("\n\t- Round Robin : %.2f ms\n", avg_waiting_time_RR);

            print_min_scheduler(
                avg_waiting_time_FCFS,
                avg_waiting_time_Priority,
                avg_waiting_time_SRTF,
                avg_waiting_time_RR);
        }
        else if (choice == 6)
        {
            break;
        }
        else
        {
            printf("\nInvalid Choice. Exiting Program.\n\n");
            break;
        }
    }
    free(process_list);
    return 0;
}
