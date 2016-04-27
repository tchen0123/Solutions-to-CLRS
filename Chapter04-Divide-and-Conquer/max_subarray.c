/*
 * Solutions-to-CLRS/Chapter04-Divide-and-Conquer/max_subarray.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "max_subarray.h"

/*
 * Search maximum subarray.
 * This function doesn't use recursion but the other method using linear time.
 */
struct maxSubarray_s MaxSubarray(int array[], int size)
{
        struct maxSubarray_s ret;
        int i, tempIndex, tempSum;

        ret.sum = tempSum = array[0];
        ret.low = ret.high = 0;
        tempIndex = 0;
        for (i = 1; i < size; i++) {
                if (tempSum < 0) { // If tempSum is less than 0, renew tempSum and tempIndex
                        tempSum = array[i];
                        tempIndex = i;
                } else { // else add array[i]
                        tempSum += array[i];
                }

                if (tempSum > ret.sum) { // Update
                        ret.sum = tempSum;
                        ret.low = tempIndex;
                        ret.high = i;
                }
        }

        return ret;
}
