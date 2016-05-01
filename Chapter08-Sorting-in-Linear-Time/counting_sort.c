/*
 * Solutions-to-CLRS/Chapter08-Sorting-in-Linear-Time/counting_sort.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "counting_sort.h"
#include <memory.h>

/*
 * Search the minimum in the array.
 */
static inline int Minimum(const int array[], const int size)
{
        int i, min;

        min = array[0];
        for (i = 1; i < size; i++) {
                if (array[i] < min) {
                        min = array[i];
                }
        }

        return min;
}

/*
 * Search the maximum in the array.
 */
static inline int Maximum(const int array[], const int size)
{
        int i, max;

        max = array[0];
        for (i = 1; i < size; i++) {
                if (array[i] > max) {
                        max = array[i];
                }
        }

        return max;
}

/*
 * Counting sort.
 * The sorting result is stored in the result  array.
 */
void CountingSort(const int array[], int result[], const int arraySize)
{
        int i, min, max, len;

        min = Minimum(array, arraySize);
        max = Maximum(array, arraySize);
        len = max - min + 1;

        // Calculate count array
        int count[len];
        memset(count, 0, sizeof(int) * len);
        for (i = 0; i < arraySize; i++) {
                count[array[i] - min]++;
        }
        for (i = 1; i < len; i++) {
                count[i] += count[i - 1];
        }

        // Stable sorting
        for (i = arraySize - 1; i >= 0; i--) {
                result[count[array[i] - min] - 1] = array[i];
                count[array[i] - min]--;
        }
}
