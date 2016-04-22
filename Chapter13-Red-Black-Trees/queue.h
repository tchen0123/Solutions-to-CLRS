/*
 * Solutions-to-CLRS/Chapter13-Red-Black-Trees/queue.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <stdlib.h>
#include "rbtree.h"

struct queueNode_s {
        struct rbtree_s *rbtree;
        struct queueNode_s *next;
};

struct queue_s {
        struct queueNode_s *front;
        struct queueNode_s *rear;
        size_t size;
};

void EnQueue(struct queue_s *queue, struct rbtree_s *rbtree);
struct rbtree_s *DeQueue(struct queue_s *queue);
int QueueIsEmpty(struct queue_s *queue);
struct queue_s *InitQueue(void);
void DeleteQueue(struct queue_s *queue);

#endif
