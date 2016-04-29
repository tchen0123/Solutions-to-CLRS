/*
 * Solutions-to-CLRS/Chapter07-Quicksort/quicksort.c
 *
 * Copyright (C) 2016  Jiawei Feng
 */

#include "quicksort.h"
#include <stdlib.h>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static int RandomPartition(int array[], int low, int high);

void QuickSort(int array[], int low, int high)
{
        if (low < high) {
                int pivotIndex = RandomPartition(array, low, high);
                QuickSort(array, low, pivotIndex - 1);
                QuickSort(array, pivotIndex + 1, high);
        }
}

/*
 * Random partition.
 * In order to prevent the worst case.
 */
static int RandomPartition(int array[], int low, int high)
{
        int randomIndex = (rand() % (high - low + 1)) + low; // Create a random array index
        Swap(&array[randomIndex], &array[high]);

        int larger, less, pivot;

        pivot = array[high];
        less = low - 1;
        for (larger = low; larger < high; larger++) {
                if (array[larger] <= pivot) {
                        less++;
                        Swap(&array[less], &array[larger]);
                }
        }
        Swap(&array[less + 1], &array[high]);

        return less + 1;
}
