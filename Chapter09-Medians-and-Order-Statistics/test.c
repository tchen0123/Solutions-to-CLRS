/*
 * Solutions-to-CLRS/Chapter09-Medians-and-Order-Statistics/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "select.h"
#include "max_min.h"
#include <stdlib.h>
#include <stdio.h>

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

        int min, max;
        MaximumAndMinimum(array, size, &max, &min);
        printf("\n\nThe maximum is %d, and the minimum is %d\n", max, min);

        int k;
        printf("\n\nPlease enter k:\n");
        scanf("%d", &k);

        if (k > size || k < 0) {
                fprintf(stderr, "k is illegal!\n");
        } else {
                printf("\nThe %d-th element of the array is %d\n", k, Select(array, 0, size - 1, k));
        }

        return 0;
}

/*
 * Randomize the array.
 */
static void RandomizeArray(int array[], int size)
{
        int i;
        for (i = 1; i < size; i++) {
                int tempIndex = rand() % i;
                Swap(&array[tempIndex], &array[i]);
        }
}
