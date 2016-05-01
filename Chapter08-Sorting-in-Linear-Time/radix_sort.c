/*
 * Solutions-to-CLRS/Chapter08-Sorting-in-Linear-Time/radix_sort.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "radix_sort.h"
#include <memory.h>

/*
 * This routine is the implementation of radix sort.
 * It divides a 32 bits integer numbers into four parts, and each part consists of 8 bits.
 */


#define SHIFT_AND_MASK(number, i) ((number >> (i * 8)) & 0x000000FF)

static inline int Minimum(int array[], int size, int index)
{
        int i, min;

        min = SHIFT_AND_MASK(array[0], index);
        for (i = 1; i < size; i++) {
                if (SHIFT_AND_MASK(array[i], index) < min) {
                        min = SHIFT_AND_MASK(array[i], index);
                }
        }

        return min;
}

static inline int Maximum(int array[], int size, int index)
{
        int i, max;

        max = SHIFT_AND_MASK(array[0], index);
        for (i = 1; i < size; i++) {
                if (SHIFT_AND_MASK(array[i], index) > max) {
                        max = SHIFT_AND_MASK(array[i], index);
                }
        }

        return max;
}

static void CountingSort(int array[], int result[], int arraySize, int index);

void RadixSort(int array[], int result[], int arraySize)
{
        int i, size;

        size = sizeof(int);
        for (i = 0; i < size; i++) {
                CountingSort(array, result, arraySize, i);

                // After one sorting, array should be updated.
                if (i < size - 1) {
                        int j;
                        for (j = 0; j < arraySize; j++) {
                                array[j] = result[j];
                        }
                }
        }
}

static void CountingSort(int array[], int result[], int arraySize, int index)
{
        int i, max, min, len;

        max = Maximum(array, arraySize, index);
        min = Minimum(array, arraySize, index);
        len = max - min + 1;

        int count[len];
        memset(count, 0, sizeof(int) * len);

        for (i = 0; i < arraySize; i++) {
                count[SHIFT_AND_MASK(array[i], index) - min]++;
        }
        for (i = 1; i < len; i++) {
                count[i] += count[i - 1];
        }

        for (i = arraySize - 1; i >= 0; i--) {
                result[count[SHIFT_AND_MASK(array[i], index) - min] - 1] = array[i];
                count[SHIFT_AND_MASK(array[i], index) - min]--;
        }
}
