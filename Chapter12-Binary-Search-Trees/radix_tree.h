/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/radix_tree.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This code is the simple operation about radix tree.
 * In this routine, each radix tree node has four children node allocated by binary digits 00, 01, 10, 11.
 * The radix tree is used to stored unsigned integer numbers.
 */


#ifndef __RADIX_TREE_H_
#define __RADIX_TREE_H_

#define CHILD_NUM    4 // children node number

struct radixTree_s {
        int count;
        unsigned int value;
        struct radixTree_s *child[CHILD_NUM];
};

void RadixTreeInsert(struct radixTree_s *treeRoot, unsigned int value);
void RadixTreeWalk(struct radixTree_s *treeRoot);
struct radixTree_s *InitRadixTree(void);

#endif
