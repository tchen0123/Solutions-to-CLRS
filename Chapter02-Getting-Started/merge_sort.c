/*
 * Solutions-to-CLRS/Chapter02-Getting-Started/merge_sort.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "merge_sort.h"

static void Merge(int array[], int head, int tail, int midd);

void MergeSort(int array[], int head, int tail)
{
        if (head < tail) {
                int midd = (head + tail) / 2;
                MergeSort(array, head, midd);
                MergeSort(array, midd + 1, tail);
                Merge(array, head, tail, midd);
        }
}

/*
 * Array merge operation.
 */
static void Merge(int array[], int head, int tail, int midd)
{
        int leftLen, rightLen;

        leftLen = midd - head + 1;
        rightLen = tail - midd;

        int left[leftLen], right[rightLen];
        int i, j;
        for (i = 0; i < leftLen; i++) {
                left[i] = array[head + i];
        }
        for (j = 0; j < rightLen; j++) {
                right[j] = array[midd + 1 + j];
        }

        int k;
        i = j = 0;
        for (k = head; k <= tail; k++) {
                if (left[i] < right[j]) {
                        array[k] = left[i];

                        /* If left array arrives the end */
                        if (++i == leftLen) {
                                k++;
                                for (; k <= tail; k++) {
                                        array[k] = right[j];
                                        j++;
                                }
                                break;
                        }
                } else {
                        array[k] = right[j];

                        /* If right array arrives the end */
                        if (++j == rightLen) {
                                k++;
                                for (; k <= tail; k++) {
                                        array[k] = left[i];
                                        i++;
                                }
                                break;
                        }
                }
        }
}
