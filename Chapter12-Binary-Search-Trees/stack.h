/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/stack.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __STACK_H_
#define __STACK_H_

#include <stdlib.h>
#include <stdbool.h>
#include "bintree.h"

/*
 * Preorder and inorder tree walk.
 */
struct preWalkNode_s {
        struct bintree_s *bintree;
        struct preWalkNode_s *prev, *next;
};

struct preWalk_s {
        struct preWalkNode_s *top;
        size_t size;
};
// prototype
struct preWalk_s *InitPreWalk(void);
void PreWalkPush(struct preWalk_s *stack, struct bintree_s *bintree);
struct bintree_s *PreWalkPop(struct preWalk_s *stack);
int PreWalkIsEmpty(struct preWalk_s *stack);
void DeletePreWalk(struct preWalk_s *stack);

/*
 * Post tree walk.
 */
struct postWalkNode_s {
        struct bintree_s *bintree;
        bool isFirst;
        struct postWalkNode_s *prev, *next;
};

struct postWalk_s {
        struct postWalkNode_s *top;
        size_t size;
};

// prototype
struct postWalk_s *InitPostWalk(void);
void PostWalkPush(struct postWalk_s *stack, struct bintree_s *bintree, bool isFirst);
struct postWalkNode_s *PostWalkPop(struct postWalk_s *stack);
int PostWalkIsEmpty(struct postWalk_s *stack);
void DeletePostWalk(struct postWalk_s *stack);

#endif
