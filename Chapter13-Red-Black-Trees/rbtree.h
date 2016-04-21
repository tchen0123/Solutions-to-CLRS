/*
 * Solutions-to-CLRS/Chapter13-Red-Black-Trees/rbtree.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __RBTREE_H_
#define __RBTREE_H_

#define RB_RED      0
#define RB_BLACK    1

struct rbtree_s {
        int value;
        int color;
        struct rbtree_s *parent;
        struct rbtree_s *left;
        struct rbtree_s *right;
};

struct rbtree_s *InitRbtreeNil(void);
struct rbtree_s *RbtreeInsert(struct rbtree_s *treeRoot, int num);
struct rbtree_s *RbtreeDelete(struct rbtree_s *treeRoot, int num);
void TreeWalkInorder(struct rbtree_s *treeRoot);
void TreeWalkInlevel(struct rbtree_s *treeRoot);
void DeleteTree(struct rbtree_s *treeRoot);

#endif
