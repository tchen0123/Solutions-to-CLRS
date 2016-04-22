/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/radix_tree.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "radix_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Insert a string to the radix tree.
 */
void RadixTreeInsert(struct radixTree_s *treeRoot, const char str[])
{
        int i, strSize;

        strSize = strlen(str);

        for (i = 0; i < strSize; i++) {
                if (treeRoot->child[str[i] - 'a'] == NULL) {
                        treeRoot->child[str[i] - 'a'] = InitRadixTree();
                }
                treeRoot = treeRoot->child[str[i] - 'a'];
        }

        treeRoot->str = (char *)malloc(sizeof(char) * (STR_SIZE + 1));
        strcpy(treeRoot->str, str);
}

/*
 * Radix tree walk preorder.
 */
void RadixTreeWalk(struct radixTree_s *treeRoot)
{
        if (treeRoot != NULL) {
                if (treeRoot->str) {
                        printf("%s\n", treeRoot->str);
                }

                int i;
                for (i = 0; i < CHILDREN_SIZE; i++) {
                        RadixTreeWalk(treeRoot->child[i]);
                }
        }
}

/*
 * Initialize the radix tree.
 */
struct radixTree_s *InitRadixTree(void)
{
        struct radixTree_s *treeRoot = (struct radixTree_s *)malloc(sizeof(struct radixTree_s));

        memset(treeRoot, 0, sizeof(struct radixTree_s));

        return treeRoot;
}
