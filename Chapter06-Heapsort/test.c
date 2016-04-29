/*
 * Solutions-to-CLRS/Chapter06-Heapsort/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "heapsort.h"
#include "Kway_merge.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_MAX_SIZE 100

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

        int array[ARRAY_MAX_SIZE]; // heapsort test
        int k, n; // k-way merge test

        printf("Please enter your choice:\n");
        printf("1.Heapsort test\n");
        printf("2.K-way merge test\n");
        scanf("%d", &select);

        switch (select) {
        case 1:
                printf("How many integer numbers do you want to input?\n");
                scanf("%d", &size);

                if (size > ARRAY_MAX_SIZE) {
                        fprintf(stderr, "Array size is limited within %d!\n", ARRAY_MAX_SIZE);
                        return 0;
                }

                for (i = 0; i < size; i++) {
                        array[i] = i + 1;
                }
                RandomizeArray(array, size);

                printf("The input array:\n");
                for (i = 0; i < size; i++) {
                        printf("%d ", array[i]);
                }
                printf("\n\n");

                HeapSort(array, size);
                printf("The sorted array:\n");
                for (i = 0; i < size; i++) {
                        printf("%d ", array[i]);
                }
                printf("\n\n");
                break;
        case 2:
                printf("Please input k: ");
                scanf("%d", &k);
                printf("Please input n: ");
                scanf("%d", &n);

                if (k > HEAP_MAX_SIZE) {
                        fprintf(stderr, "Heap size is limited within %d!\n", HEAP_MAX_SIZE);
                        return 0;
                }

                KwayMerge(k, n);
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
