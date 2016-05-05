/*
 * Solutions-to-CLRS/Chapter02-Getting-Started/inversion.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "inversion.h"

static unsigned int inversionNum;

static void MergeSort(int array[], unsigned int low, unsigned int high);
static void Merge(int array[], unsigned int low, unsigned int midd, unsigned int high);

/*
 * Calculate the number of inversions in the array.
 */
unsigned int FindInversion(int array[], unsigned int size)
{
        inversionNum = 0;
        MergeSort(array, 0, size - 1);

        return inversionNum;
}

/*
 * Merge sort.
 */
static void MergeSort(int array[], unsigned int low, unsigned int high)
{
        if (low < high) {
                unsigned int midd = (low + high) / 2;
                MergeSort(array, low, midd);
                MergeSort(array, midd + 1, high);
                Merge(array, low, midd, high);
        }
}

/*
 * Merge the array, and calculate the number of inversions in the array.
 */
static void Merge(int array[], unsigned int low, unsigned int midd, unsigned int high)
{
        unsigned int leftLen = 0, i = 0;
        leftLen = midd - low + 1;
        int left[leftLen];
        for (i = 0; i < leftLen; i++) {
                left[i] = array[low + i];
        }

        unsigned int rightLen = 0, j = 0;
        rightLen = high - midd;
        int right[rightLen];
        for (j = 0; j < rightLen; j++) {
                right[j] = array[midd + 1 + j];
        }

        i = j = 0;
        unsigned int k = 0;
        for (k = low; k <= high; k++) {
                if (left[i] <= right[j]) {
                        array[k] = left[i];

                        if (++i == leftLen) {
                                for (++k; k <= high; k++) {
                                        array[k] = right[j++];
                                }
                                break;
                        }
                } else {
                        inversionNum += leftLen - i;

                        array[k] = right[j];

                        if (++j == rightLen) {
                                for (++k; k <= high; k++) {
                                        array[k] = left[i++];
                                }
                                break;
                        }
                }
        }
}
