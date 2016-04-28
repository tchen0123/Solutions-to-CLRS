/*
 * Solutions-to-CLRS/Chapter06-Heapsort/heapsort.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "heapsort.h"
#include "heap.h"

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

/*
 * Heap sort.
 */
void HeapSort(int array[], int size)
{
        // Build a min heap
        BuildMaxHeap(array, size);

        int i;
        for (i = size - 1; i >= 1; i--) {
                Swap(&array[0], &array[i]);
                size--;
                MaxHeapify(array, size, 0);
        }
}
