/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/queue.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "ostree.h"

struct queueNode_s {
        struct ostree_s *ostree;
        struct queueNode_s *prev, *next;
};

struct queue_s {
        struct queueNode_s *head, *tail;
        unsigned int size;
};

struct queue_s *InitQueue(void);
void EnQueue(struct queue_s *queue, struct ostree_s *ostree);
struct ostree_s *DeQueue(struct queue_s *queue);
bool QueueIsEmpty(struct queue_s *queue);
void DeleteQueue(struct queue_s *queue);

#endif
