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

        return max;
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

        return min;
}

/*
 * Search the maximum and minimum of array.
 */
void MaximumAndMinimum(int array[], int size, int *max, int *min)
{
        int i, tempMax, tempMin;

        tempMax = tempMin = array[0];
        for (i = 0; i < size - 1; i += 2) {
                if (array[i] > array[i + 1]) {
                        if (array[i] > tempMax) {
                                tempMax = array[i];
                        }
                        if (array[i + 1] < tempMin) {
                                tempMin = array[i + 1];
                        }
                } else {
                        if (array[i + 1] > tempMax) {
                                tempMax = array[i + 1];
                        }
                        if (array[i] < tempMin) {
                                tempMin = array[i];
                        }
                }
        }

        *max = tempMax;
        *min = tempMin;
}
