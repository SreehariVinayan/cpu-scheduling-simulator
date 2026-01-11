#ifndef HEAP
#define HEAP

#include "structs.h"
#include "utils/comparisonFns.h"

typedef struct Process_Heap
{
    Process *processes;
    ProcessCompare comparision_function;
    int size;
    int capacity;
} Process_Heap;

Process_Heap *createHeap(int capacity, int comparison_function_value)
{
    Process_Heap *heap = (Process_Heap *)malloc(sizeof(Process_Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->processes = (Process *)malloc(capacity * sizeof(Process));
    switch (comparison_function_value)
    {
    case 1:
        heap->comparision_function = compare_on_reamining_burst;
        break;
    case 2:
        heap->comparision_function = compare_on_priority_value;
        break;
    default:
        break;
    }
    return heap;
}

void printHeap(Process_Heap *heap)
{
    for (int i = 0; i < heap->size; ++i)
        printf("P%d ", heap->processes[i].pid);
    printf("\n");
}

void swap(Process *a, Process *b)
{
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify_up(Process_Heap *heap, int index)
{
    int parent = index / 2;

    if (parent >= 0 && heap->comparision_function(&heap->processes[index],
                                                  &heap->processes[parent]) < 0)
    {
        swap(&heap->processes[index], &heap->processes[parent]);
        min_heapify_up(heap, parent);
    }
}

void heapify(Process_Heap *heap, int index)
{
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    if ((left_child < heap->size && heap->comparision_function(&heap->processes[left_child], &heap->processes[index]) < 0) || (right_child < heap->size && heap->comparision_function(&heap->processes[right_child], &heap->processes[index]) < 0))
    {
        int replacement = heap->comparision_function(&heap->processes[left_child], &heap->processes[right_child]) <= 0
                              ? left_child
                              : right_child;
        swap(&heap->processes[replacement], &heap->processes[index]);
        heapify(heap, replacement);
    }
}

void insertHeap(Process_Heap *heap, Process process)
{
    if (heap->size == heap->capacity)
    {
        printf("Element: P%d", process.pid);
        printf("Heap overflow\n");
        return;
    }

    heap->size++;
    int i = heap->size - 1;
    heap->processes[i] = process;

    min_heapify_up(heap, i);
}

int isHeapEmpty(Process_Heap *heap)
{
    return heap->size == 0;
}

Process extractMin(Process_Heap *heap)
{
    if (heap->size == 0)
    {
        heap->processes[0].is_not_null = 0;
        return heap->processes[0];
    }
    if (heap->size == 1)
    {
        heap->size--;
        return heap->processes[0];
    }

    Process root = heap->processes[0];
    heap->processes[0] = heap->processes[heap->size - 1];
    heap->size--;

    heapify(heap, 0);
    return root;
}

#endif