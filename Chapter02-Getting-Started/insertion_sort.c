/*
 * Solutions-to-CLRS/Chapter02-Getting-Started/insertion_sort.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "insertion_sort.h"

/*
 * Insertion sort.
 */
void InsertionSort(int array[], const int size)
{
        int i;

        for (i = 1; i < size; i++) {
                int j, key;

                j = i - 1;
                key = array[i];
                while (j >= 0 && array[j] > key) {
                        array[j + 1] = array[j];
                        j--;
                }
                array[j + 1] = key;
        }
}
