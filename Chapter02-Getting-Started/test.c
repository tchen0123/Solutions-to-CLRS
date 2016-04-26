/*
 * Solutions-to-CLRS/Chapter02-Getting-Started/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "insertion_sort.h"
#include "binary_sum.h"
#include <stdio.h>
#include <stdlib.h>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static void RandomizeArray(int array[], int size);
static void CreateBinary(int array[], int size);

int main(void)
{
        int size, i, select;

        printf("1.Insertion sort test\n");
        printf("2.Binary numbers sum test\n");
        printf("Please enter your choice:\n");
        scanf("%d", &select);

        printf("How many integer numbers do you want to enter?\n");
        scanf("%d", &size);

        int array[size];
        int binaryA[size], binaryB[size], binarySum[11];

        switch (select) {
        case 1:
                for (i = 0; i < size; i++) {
                        array[i] = i + 1;
                }

                RandomizeArray(array, size);

                printf("The input array:\n");
                for (i = 0; i < size; i++) {
                        printf("%d ", array[i]);
                }
                printf("\n\n");

                InsertionSort(array, size);

                printf("The array sorted:\n");
                for (i = 0; i < size; i++) {
                        printf("%d ", array[i]);
                }
                printf("\n\n");
                break;
        case 2:
                /* Create binary number array */
                CreateBinary(binaryA, size);
                CreateBinary(binaryB, size);

                /* Binary sum */
                BinarySum(binaryA, binaryB, size, binarySum);

                printf(" ");
                for (i = 0; i < size; i++) {
                        printf("%d", binaryA[i]);
                }
                printf("\n+\n");

                printf(" ");
                for (i = 0; i < size; i++) {
                        printf("%d", binaryB[i]);
                }
                printf("\n=\n");

                for (i = 0; i < size + 1; i++) {
                        printf("%d", binarySum[i]);
                }
                printf("\n");
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

/*
 * Create binary number array.
 */
static void CreateBinary(int array[], int size)
{
        int i;
        for (i = 0; i < size; i++) {
                array[i] = rand() % 2;
        }
}
