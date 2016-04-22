/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>


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

        scanf("%d", &size);

        int array[size];
        for (i = 0; i < size; i++) {
                array[i] = i + 1;
        }
        RandomizeArray(array, size);

        struct bintree_s *treeRoot = NULL;
        for (i = 0; i < size; i++) {
                int temp = array[i];
                printf("%d ", temp);
                treeRoot = BintreeInsert(treeRoot, temp);
        }
        printf("\n\n");

        TreeWalkInorder(treeRoot);
        printf("\n\n");

        TreeWalkInlevel(treeRoot);
        printf("\n\n");

        return 0;
}

static void RandomizeArray(int array[], int size)
{
        int i;
        for (i = 1; i < size; i++) {
                int tempIndex = rand() % i;
                Swap(&array[i], &array[tempIndex]);
        }
}
