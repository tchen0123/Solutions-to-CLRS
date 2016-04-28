/*
 * Solutions-to-CLRS/Chapter06-Heapsort/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "heapsort.h"
#include "k_way_merge.h"
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
        int size, select, i;

        printf("Please enter your choice:\n");
        printf("1.Heapsort test\n");
        printf("2.Priority queue test\n");
        scanf("%d", &select);

        printf("How many integer numbers do you want to input?\n");
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

        switch (select) {
        case 1:
                HeapSort(array, size);
                printf("The sorted array:\n");
                for (i = 0; i < size; i++) {
                        printf("%d ", array[i]);
                }
                printf("\n\n");
                break;
        case 2:
                KwayMerge(10, 7);
                printf("\n\n");
                break;
        }

        return 0;
}

/*
 * Randomize array.
 */
static void RandomizeArray(int array[], int size)
{
        int i;
        for (i = 1; i < size; i++) {
                int tempIndex = rand() % i;
                Swap(&array[i], &array[tempIndex]);
        }
}
