/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/radix_tree.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This code is the simple operation about radix tree.
 * In this routine, each radix tree node has four children node allocated by binary digits 00, 01, 10, 11.
 * The radix tree is used to stored unsigned integer numbers.
 */

#include "radix_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

/*
 * Create a new node.
 */
static struct radixTree_s *CreateNode(void)
{
        struct radixTree_s *newNode = (struct radixTree_s *)malloc(sizeof(struct radixTree_s));
        memset(newNode, 0, sizeof(struct radixTree_s));

        return newNode;
}

/*
 * Insert a value into the radix tree.
 */
void RadixTreeInsert(struct radixTree_s *treeRoot, unsigned int value)
{
        unsigned int size, i;

        size = 32;
        for (i = 0; i < size; i += 2) {
                unsigned int index = 3 - ((value >> (30 - i)) & 0x00000003);

                if (treeRoot->child[index] == NULL) {
                        treeRoot->child[index] = CreateNode();
                }
                treeRoot = treeRoot->child[index];
        }
        treeRoot->value = value;
        treeRoot->count++;
}

/*
 * Radix tree walk preorder.
 */
void RadixTreeWalk(struct radixTree_s *treeRoot)
{
        if (treeRoot != NULL) {
                if (treeRoot->count != 0) {
                        int i;

                        for (i = 0; i < 32; i++) {
                                if ((treeRoot->value >> (31 - i)) & 0x00000001) {
                                        printf("1");
                                } else {
                                        printf("0");
                                }
                        }
                        printf("\n");
                }

                int i;
                for (i = 0; i < CHILD_NUM; i++) {
                        RadixTreeWalk(treeRoot->child[i]);
                }
        }
}

/*
 * Initialize radix tree.
 */
struct radixTree_s *InitRadixTree(void)
{
        struct radixTree_s *treeRoot = CreateNode();

        return treeRoot;
}

/*
 * Delete the whole radix tree.
 */
void DeleteRadixTree(struct radixTree_s *treeRoot)
{
        if (treeRoot != NULL) {
                int i;
                for (i = 0; i < CHILD_NUM; i++) {
                        DeleteRadixTree(treeRoot->child[i]);
                }
                free(treeRoot);
        }
}
