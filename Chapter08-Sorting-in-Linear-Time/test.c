/*
 * Solutions-to-CLRS/Chapter08-Sorting-in-Linear-Time/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "counting_sort.h"
#include "radix_sort.h"
#include "bucket_sort.h"
#include <stdio.h>
#include <stdlib.h>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static void CreateArray(int array[], const int size);

int main(void)
{
        int size, i, select;

        printf("Please enter your choice:\n");
        printf("1.Counting sort test\n");
        printf("2.Radix sort test\n");
        printf("3.Bucket sort test\n");
        scanf("%d", &select);

        printf("How many integer numbers do you want to input?\n");
        scanf("%d", &size);

        int array[size], result[size];
        CreateArray(array, size);

        printf("The original array:\n");
        for (i = 0; i < size; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");

        switch (select) {
        case 1:
                CountingSort(array, result, size);

                printf("The sorted array:\n");
                for (i = 0; i < size; i++) {
                        printf("%d ", result[i]);
                }
                printf("\n\n");
                break;
        case 2:
                RadixSort(array, result, size);

                printf("The sorted array:\n");
                for (i = 0; i < size; i++) {
                        printf("%d ", result[i]);
                }
                break;
        case 3:
                BucketSort(array, size);

                printf("The sorted array:\n");
                for (i = 0; i < size; i++) {
                        printf("%d ", array[i]);
                }
                break;
        }

        return 0;
}

/*
 * Create random array.
 */
static void CreateArray(int array[], const int size)
{
        int i;

        for (i = 0; i < size; i++) {
                array[i] = rand() % (size * size * size);
        }
}
