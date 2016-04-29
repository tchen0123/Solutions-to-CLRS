/*
 * Solutions-to-CLRS/Chapter08-Sorting-in-Linear-Time/counting_sort.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "counting_sort.h"
#include <memory.h>

/*
 * Search the minimum.
 */
static inline int Minimum(int array[], int arraySize)
{
        int i, min;
        min = array[0];
        for (i = 1; i < arraySize; i++) {
                if (array[i] < min) {
                        min = array[i];
                }
        }

        return min;
}

/*
 * Search the maximum.
 */
static inline int Maximum(int array[], int arraySize)
{
        int i, max;
        max = array[0];
        for (i = 1; i < arraySize; i++) {
                if (array[i] > max) {
                        max = array[i];
                }
        }

        return max;
}

/*
 * Counting sort.
 * The sort result is stored in the result array.
 */
void CountingSort(int array[], int result[], int arraySize)
{
        int i, min, max, len;

        // calculate the len as the index offset
        min = Minimum(array, arraySize);
        max = Maximum(array, arraySize);
        len = max - min + 1;

        int count[len];
        memset(count, 0, sizeof(int) * len);

        // calculate count array
        for (i = 0; i < arraySize; i++) {
                count[array[i] - min]++;
        }
        for (i = 1; i < len; i++) {
                count[i] += count[i - 1];
        }

        for (i = arraySize - 1; i >= 0; i--) {
                result[count[array[i] - min] - 1] = array[i];
                count[array[i] - min]--;
        }
}
