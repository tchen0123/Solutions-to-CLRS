/*
 * Solutions-to-CLRS/Chapter09-Medians-and-Order-Statistics/max_min.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "max_min.h"
#include <stdlib.h>

/*
 * Search the maximum of array.
 */
int Maximum(int array[], int size)
{
        int i, max;

        max = array[0];
        for (i = 1; i < size; i++) {
                if (max < array[i]) {
                        int temp = max;
                        max = array[i];
                        array[i] = temp;
                }
        }
}

/*
 * Search the minimum of array.
 */
int Minimum(int array[], int size)
{
        int i, min;

        min = array[0];
        for (i = 1; i < size; i++) {
                if (min > array[i]) {
                        int temp = min;
                        min = array[i];
                        array[i] = temp;
                }
        }
}

/*
 * Search the maximum and minimum of array.
 */
void MaximumAndMinimum(int array[], int size, int *max, int *min)
{
        int i, tempMax, tempMin;

        for (i = 0; i < size - 1; i += 2) {
                if (array[i] > array[i + 1]) {
                        tempMax = array[i];
                        tempMin = array[i + 1];
                } else {
                        tempMax = array[i + 1];
                        tempMin = array[i];
                }
        }
        for (; i < size; i++) {
                if (array[i] > tempMax) {
                        tempMax = array[i];
                } else if (array[i] < tempMin) {
                        tempMin = array[i];
                }
        }

        *max = tempMax;
        *min = tempMin;
}
