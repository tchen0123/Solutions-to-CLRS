/*
 * Solutions-to-CLRS/Chapter13-Red-Black-Trees/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "rbtree.h"
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

        struct rbtree_s *treeRoot = InitRbtreeNil();
        for (i = 0; i < size; i++) {
                int temp = array[i];
                printf("%d ", temp);
                treeRoot = RbtreeInsert(treeRoot, temp);
        }
        printf("\n\n");

        TreeWalkInorder(treeRoot);
        printf("\n\n");

        TreeWalkInlevel(treeRoot);
        printf("\n\n");

        for (i = 0; i < size; i++) {
                treeRoot = RbtreeDelete(treeRoot, i + 1);
                TreeWalkInlevel(treeRoot);
                printf("\n\n");
        }

        DeleteTree(treeRoot);

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
