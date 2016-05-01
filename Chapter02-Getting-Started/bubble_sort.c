/*
 * Solutions-to-CLRS/Chapter02-Getting-Started/bubble_sort.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "bubble_sort.h"

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

void BubbleSort(int array[], const int size)
{
        int i, j;

        for (i = 0; i < size; i++) {
                for (j = size - 1; j >= i + 1; j--) {
                        if (array[j] < array[j - 1]) {
                                Swap(&array[j], &array[j - 1]);
                        }
                }
        }
}
