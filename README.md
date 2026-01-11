# CPU Scheduling Simulator

A C-based simulation of classical CPU scheduling algorithms used in operating systems.  
This project demonstrates scheduling behavior, visualizes execution using Gantt charts, and compares
average waiting times to evaluate algorithm performance.
This project was developed as part of the **_Semester S4 Operating Systems Lab_** (Experiment 9) (AIM included as comment in main.c).

---

## Features

- Interactive, menu-driven CLI
- Supports multiple CPU scheduling algorithms
- Gantt chart visualization for each algorithm
- Accurate computation of waiting times
- Side-by-side comparison of scheduling performance

### Implemented Algorithms

- **First Come First Serve (FCFS)**
- **Shortest Remaining Time First (SRTF)** (Preemptive SJF)
- **Non-preemptive Priority Scheduling**
- **Round Robin Scheduling** (Configurable Time Quantum)

---

## Project Structure

```
cpu-scheduling-simulator/
├── src/
│   └── main.c
│
├── include/
│   ├── algorithms/
│   │   ├── FCFS.h
│   │   ├── SRTF.h
│   │   ├── Priority.h
│   │   └── RoundRobin.h
│   │
│   ├── core/
│   │   ├── structs.h
│   │   ├── queue.h
│   │   ├── heap.h
│   │   └── sortAT.h
│   │
│   └── utils/
│       ├── gantt.h
│       ├── log_queue.h
│       ├── comparisonFns.h
│       └── utils.h
│
├── .gitignore
├── README.md
```

---

## Build & Run

### Compilation

```bash
gcc src/main.c -Iinclude -o cpu_scheduler -lm
```

### Execution

```bash
./cpu_scheduler
```

---

## Sample Program Output

The simulator allows the user to choose a scheduling algorithm and displays:

- Gantt chart of execution
- Waiting time for each process
- Average waiting time
- Best algorithm based on minimum average waiting time

Example output:

```
	Round Robin
	-----------
  Enter quantum value = 3


	Gantt Chart:
	--------------------------------------------------------------------
	| P1  | P1  | P2  | P1  | P3  | P2 | P4 | P5  | P1 | P3  | P5 | P3 |
	--------------------------------------------------------------------
	0     3     6     9     12    15   17   19    22   23    26   28   30


	PID	|	Waiting Time
	P1	|	13
	P2	|	7
	P3	|	15
	P4	|	8
	P5	|	14

	Average waiting time = 11.40 ms.

```

Example comparison output:

```
Average Waiting Times
- FCFS : 8.60 ms
- SRTF : 6.20 ms
- Non-preemptive Priority : 7.40 ms
- Round Robin : 11.40 ms

Shortest Average Waiting Time: SRTF (6.20 ms)
```

---

## Scheduling Metrics

- **Waiting Time**  
  `Waiting Time = Completion Time − Arrival Time − Burst Time`

- **Turnaround Time**  
  `Turnaround Time = Completion Time − Arrival Time`

These formulas are applied consistently across all algorithms.

## Notes

- Higher numeric value indicates higher priority
- Preempted processes are re-enqueued before same-time arrivals in Round Robin
