/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/radix_tree.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __RADIX_TREE_H_
#define __RADIX_TREE_H_

#define CHILDREN_SIZE    26 // tree children node size

#define STR_SIZE    10 // string size

struct radixTree_s {
        char *str;
        struct radixTree_s *child[CHILDREN_SIZE];
};

void RadixTreeInsert(struct radixTree_s *treeRoot, const char str[]);
void RadixTreeWalk(struct radixTree_s *treeRoot);
struct radixTree_s *InitRadixTree(void);

#endif
