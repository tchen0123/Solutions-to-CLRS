/*
 * Solutions-to-CLRS/Chapter10-Elementary-Data-Structures/list.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static void RandomizeArray(int array[], int size);

int main(void)
{
        int size, i;

        printf("How many integer numbers do you want to enter?\n");
        scanf("%d", &size);

        int array[size];
        for (i = 0; i < size; i++) {
                array[i] = i + 1;
        }

        RandomizeArray(array, size);

        printf("The input array:\n");
        struct list_s *listHead = NULL;
        for (i = 0; i < size; i++) {
                printf("%d ", array[i]);
                listHead = ListInsert(listHead, array[i]);
        }
        printf("\n\n");

        printf("List walk:\n");
        ListWalk(listHead);
        printf("\n\n");

        printf("List invert:\n");
        ListInvert(listHead);
        printf("\n\n");

        return 0;
}

/*
 * Randomize the array.
 */
static void RandomizeArray(int array[], int size)
{
        int i;
        for (i = 1; i < size; i++) {
                int tempIndex = rand() % i;
                Swap(&array[i], &array[tempIndex]);
        }
}
