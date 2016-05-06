/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/ostree.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __OSTREE_H_
#define __OSTREE_H_


#define RB_RED      0
#define RB_BLACK    1


struct ostree_s {
        int value;
        bool color;
        unsigned int size;
        struct ostree_s *parent;
        struct ostree_s *left, *right;
};

struct ostree_s *InitOstreeNil(void);
struct ostree_s *OstreeInsert(struct ostree_s *treeRoot, int num);
struct ostree_s *OstreeDelete(struct ostree_s *treeRoot, int num);
void OstreeWalkBylevel(struct ostree_s *treeRoot);
struct ostree_s *OstreeSelect(struct ostree_s *treeRoot, unsigned int rank);
unsigned int OstreeRank(struct ostree_s *treeRoot, struct ostree_s *targetPtr);
void DeleteOstree(struct ostree_s *treeRoot);
struct ostree_s *OstreeSearch(struct ostree_s *treeRoot, int num);

#endif
