/*
 * Solutions-to-CLRS/Chapter02-Getting-Started/merge_sort.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "merge_sort.h"

static void Merge(int array[], int low, int high, int midd);

void MergeSort(int array[], int low, int high)
{
        if (low < high) {
                int midd = (low + high) / 2;
                MergeSort(array, low, midd);
                MergeSort(array, midd + 1, high);
                Merge(array, low, high, midd);
        }
}

/*
 * Array merge operation.
 */
static void Merge(int array[], int low, int high, int midd)
{
        int leftLen, rightLen;

        leftLen = midd - low + 1;
        rightLen = high - midd;

        int left[leftLen], right[rightLen];
        int i, j;
        for (i = 0; i < leftLen; i++) {
                left[i] = array[low + i];
        }
        for (j = 0; j < rightLen; j++) {
                right[j] = array[midd + 1 + j];
        }

        int k;
        i = j = 0;
        for (k = low; k <= high; k++) {
                if (left[i] < right[j]) {
                        array[k] = left[i];

                        // If left array arrives the end
                        if (++i == leftLen) {
                                k++;
                                for (; k <= high; k++) {
                                        array[k] = right[j];
                                        j++;
                                }
                                break;
                        }
                } else {
                        array[k] = right[j];

                        // If right array arrives the end
                        if (++j == rightLen) {
                                k++;
                                for (; k <= high; k++) {
                                        array[k] = left[i];
                                        i++;
                                }
                                break;
                        }
                }
        }
}
