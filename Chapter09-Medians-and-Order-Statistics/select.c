/*
 * Solutions-to-CLRS/Chapter09-Medians-and-Order-Statistics/select.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "select.h"
#include <stdlib.h>

/*
 * Select the randomed number between head and tail.
 */
static inline int Random(int head, int tail)
{
        int len = tail - head + 1;

        return ((rand() % len) + head);
}

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static int RandomPartition(int array[], int head, int tail);

/*
 * Select the K-th element fo array.
 */
int Select(int array[], int head, int tail, int k)
{
        if (head == tail) {
                return array[head];
        }

        int pivotIndex, len;

        pivotIndex = RandomPartition(array, head, tail);
        len = pivotIndex - head + 1;

        if (len == k) {
                return array[pivotIndex];
        } else if (len > k) {
                return Select(array, head, pivotIndex - 1, k);
        } else {
                return Select(array, pivotIndex + 1, tail, k - len);
        }
}

/*
 * Partition randomly.
 */
static int RandomPartition(int array[], int head, int tail)
{
        int tempIndex = Random(head, tail);

        Swap(&array[tempIndex], &array[tail]);

        int larger, less, pivot;

        pivot = array[tail];
        less = head - 1;
        for (larger = head; larger < tail; larger++) {
                if (array[larger] < pivot) {
                        less++;
                        Swap(&array[less], &array[larger]);
                }
        }

        Swap(&array[tail], &array[less + 1]);

        return less + 1;
}
