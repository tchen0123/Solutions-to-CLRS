/*
 * Solutions-to-CLRS/Chapter07-Quicksort/test.c
 *
 * Copyright (C) 2016  Jiawei Feng
 */

#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static void RandomizeArray(int array[], int size);

int main(void)
{
        int size, i;

        printf("How many integer numbers do you want to enter?\n");
        scanf("%d", &size);

        int array[size];
        for (i = 0; i < size; i++) {
                array[i] = i + 1;
        }

        RandomizeArray(array, size);

        printf("The input array:\n");
        for (i = 0; i < size; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");

        QuickSort(array, 0, size - 1);

        printf("The sorted array:\n");
        for (i = 0; i < size; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");

        return 0;
}

/*
 * Randomize array.
 */
static void RandomizeArray(int array[], int size)
{
        int i;
        for (i = 1; i < size; i++) {
                int index = rand() % i;
                Swap(&array[index], &array[i]);
        }
}
