/*
 * Solutions-to-CLRS/Chapter04-Divide-and-Conquer/max_subarray.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __MAX_SUBARRAY_H_
#define __MAX_SUBARRAY_H_

// max subarray structure */
struct maxSubarray_s {
        int low;
        int high;
        int sum;
};

struct maxSubarray_s MaxSubarray(int array[], int size);
struct maxSubarray_s FindMaxSubarray(int array[], int low, int high);

#endif
