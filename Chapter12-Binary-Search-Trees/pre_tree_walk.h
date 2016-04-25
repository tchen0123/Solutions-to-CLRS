/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/pre_tree_walk.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the implementation of preorder and inorder tree walk stack.
 */

#ifndef __PRE_TREE_H_
#define __PRE_TREE_H_

#include <stdlib.h>
#include "bintree.h"

struct preWalkNode_s {
        struct bintree_s *bintree;
        struct preWalkNode_s *prev, *next;
};

struct preWalk_s {
        struct preWalkNode_s *top;
        size_t size;
};

struct preWalk_s *InitPreWalk(void);
void PreWalkPush(struct preWalk_s *stack, struct bintree_s *bintree);
struct bintree_s *PreWalkPop(struct preWalk_s *stack);
int PreWalkIsEmpty(struct preWalk_s *stack);
void DeletePreWalk(struct preWalk_s *stack);

#endif
