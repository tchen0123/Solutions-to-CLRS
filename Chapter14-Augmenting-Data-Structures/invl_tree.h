/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/invl_tree.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __INVL_TREE_H_
#define __INVL_TREE_H_

#define RB_RED      0
#define RB_BLACK    1


// interval
struct invl_s {
        int low;
        int high;
};

struct invlTree_s {
        struct invl_s interval;
        bool color;
        int maxEndpoint;
        struct invlTree_s *parent;
        struct invlTree_s *left, *right;
};


struct invlTree_s *InitInvltreeNil(void);
struct invlTree_s *InvltreeInsert(struct invlTree_s *root, struct invl_s interval);
struct invlTree_s *InvltreeDelete(struct invlTree_s *root, struct invl_s interval);
struct invlTree_s *InvltreeSearch(struct invlTree_s *root, struct invl_s interval);
void InvltreeWalkBylevel(struct invlTree_s *root);
void InvltreeWalkInorder(struct invlTree_s *root);
void DeleteInvltree(struct invlTree_s *root);

#endif
