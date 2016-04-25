/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "bintree.h"
#include "radix_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Swap two integer numbers.
 */
static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static void RandomizeArray(int array[], int size);

int main(void)
{
        int size, i, select;

        printf("1.Binary search tree test\n");
        printf("2.Radix tree test\n");
        printf("Please enter your choice: ");
        scanf("%d", &select);

        printf("How many integer numbers do you want to input?\n");
        scanf("%d", &size);

        int array[size];
        for (i = 0; i < size; i++) {
                array[i] = i + 1;
        }
        RandomizeArray(array, size);

        printf("The input array is shown as follows:\n");
        struct bintree_s *binTree = NULL;
        for (i = 0; i < size; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");

        switch (select) {
        case 1:
                for (i = 0; i < size; i++) {
                        binTree = BintreeInsert(binTree, array[i]);
                }

                printf("Tree walk inorder:\n");
                TreeWalkInorder(binTree);
                printf("\n\n");

                printf("Tree walk preorder:\n");
                TreeWalkPreorder(binTree);
                printf("\n\n");

                printf("Tree walk inlevel:\n");
                TreeWalkInlevel(binTree);
                printf("\n\n");

                BintreeInvert(binTree);
                printf("\n\n");

                printf("Tree delete test:\n");
                for (i = 0; i < size; i++) {
                        binTree = BintreeDelete(binTree, i);
                        TreeWalkInlevel(binTree);
                        printf("\n\n");
                }
                DeleteBinTree(binTree);
                break;
        case 2:
                printf("Radix tree test:\n");
                struct radixTree_s *radixTree = InitRadixTree();
                for (i = 0; i < size; i++) {
                        RadixTreeInsert(radixTree, array[i]);
                }
                RadixTreeWalk(radixTree);
                printf("\n\n");
                DeleteRadixTree(radixTree);
                break;
        }

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
