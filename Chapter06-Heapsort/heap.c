/*
 * Solutions-to-CLRS/Chapter06-Heapsort/heap.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "heap.h"

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

/*
 * Maintain the property of max heap.
 */
void MaxHeapify(int array[], int size, int i)
{
        int largest;

        if (LEFT(i) < size && array[LEFT(i)] > array[i]) {
                largest = LEFT(i);
        } else {
                largest = i;
        }

        if (RIGHT(i) < size && array[RIGHT(i)] > array[largest]) {
                largest = RIGHT(i);
        }

        if (largest != i) {
                Swap(&array[largest], &array[i]);
                MaxHeapify(array, size, largest);
        }
}

/*
 * Maintain the property of min heap.
 */
void MinHeapify(int array[], int size, int i)
{
        int least;

        if (LEFT(i) < size && array[LEFT(i)] < array[i]) {
                least = LEFT(i);
        } else {
                least = i;
        }

        if (RIGHT(i) < size && array[RIGHT(i)] < array[least]) {
                least = RIGHT(i);
        }

        if (least != i) {
                Swap(&array[least], &array[i]);
                MinHeapify(array, size, least);
        }
}

/*
 * Build a max heap.
 */
void BuildMaxHeap(int array[], int size)
{
        int i;
        for (i = size / 2; i >= 0; i--) {
                MaxHeapify(array, size, i);
        }
}

/*
 * Build a min heap.
 */
void BuildMinHeap(int array[], int size)
{
        int i;
        for (i = size / 2; i >= 0; i--) {
                MinHeapify(array, size, i);
        }
}
