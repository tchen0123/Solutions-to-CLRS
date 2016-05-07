/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/invltree_queue.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the implementation of invltree walk queue.
 */

#ifndef __INVLTREE_QUEUE_H_
#define __INVLTREE_QUEUE_H_

#include "invl_tree.h"

struct invlqueueNode_s {
        struct invlTree_s *invlTree;
        struct invlqueueNode_s *next;
};

struct invlqueue_s {
        struct invlqueueNode_s *head, *tail;
        unsigned int size;
};

struct invlqueue_s *InitInvlqueue(void);
void EnInvlqueue(struct invlqueue_s *queue, struct invlTree_s *invlTree);
struct invlTree_s *DeInvlqueue(struct invlqueue_s *queue);
bool InvlqueueIsEmpty(struct invlqueue_s *queue);
void DeleteInvlqueue(struct invlqueue_s *queue);

#endif
