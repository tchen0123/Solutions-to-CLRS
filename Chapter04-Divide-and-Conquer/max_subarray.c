/*
 * Solutions-to-CLRS/Chapter04-Divide-and-Conquer/max_subarray.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "max_subarray.h"

static struct maxSubarray_s FindMaxSubarrayCrossing(int array[], int low, int midd, int high);

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

/*
 * Search the maximum subarray using recursion.
 */
struct maxSubarray_s FindMaxSubarray(int array[], int low, int high)
{
        struct maxSubarray_s ret;

        if (low == high) {
                ret.low = low;
                ret.high = high;
                ret.sum = array[low];

                return ret;
        }

        int midd;
        struct maxSubarray_s leftMax, rightMax, crossMax;

        midd = (low + high) / 2;

        leftMax = FindMaxSubarray(array, low, midd);
        rightMax = FindMaxSubarray(array, midd + 1, high);
        crossMax = FindMaxSubarrayCrossing(array, low, midd, high);

        if (leftMax.sum >= rightMax.sum && leftMax.sum >= crossMax.sum) {
                ret = leftMax;
        } else if (rightMax.sum >= leftMax.sum && rightMax.sum >= crossMax.sum) {
                ret = rightMax;
        } else {
                ret = crossMax;
        }

        return ret;
}

/*
 * Search the maximum subarray crossing the array.
 */
static struct maxSubarray_s FindMaxSubarrayCrossing(int array[], int low, int midd, int high)
{
        int i, tempSum;

        // Search the left half maximum subarray.
        int leftIndex, leftSum;
        tempSum = leftSum = 0;
        leftIndex = midd;
        for (i = midd; i >= low; i--) {
                tempSum += array[i];
                if (tempSum > leftSum) {
                        leftSum = tempSum;
                        leftIndex = i;
                }
        }

        // Search the right half maximum subarray.
        int rightIndex, rightSum;
        tempSum = rightSum = 0;
        rightIndex = midd + 1;
        for (i = midd + 1; i <= high; i++) {
                tempSum += array[i];
                if (tempSum > rightSum) {
                        rightSum = tempSum;
                        rightIndex = i;
                }
        }

        struct maxSubarray_s ret = {
                .low = leftIndex,
                .high = rightIndex,
                .sum = leftSum + rightSum
        };

        return ret;
}
