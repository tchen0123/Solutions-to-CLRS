/*
 * Solutions-to-CLRS/Chapter04-Divide-and-Conquer/max_subarray.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "max_subarray.h"

/*
 * Search maximum subarray.
 */
void MaxSubarray(int array[], int size, int *maxLow, int *maxHigh, int *maxSum)
{
        int i, tempSum, tempIndex;

        tempSum = *maxSum = array[0];
        tempIndex = 0;
        for (i = 1; i < size; i++) {
                if (tempSum < 0) { // If tempSum is less than 0
                        tempSum = array[i];
                        tempIndex = i;
                } else {
                        tempSum += array[i];
                }

                // Update
                if (tempSum > *maxSum) {
                        *maxSum = tempSum;
                        *maxLow = tempIndex;
                        *maxHigh = i;
                }
        }
}
