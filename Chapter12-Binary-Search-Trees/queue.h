/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/queue.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <stdlib.h>
#include "bintree.h"

struct queueNode_s {
        struct bintree_s *bintree;
        struct queueNode_s *next;
};

struct queue_s {
        struct queueNode_s *front;
        struct queueNode_s *rear;
        size_t size;
};

void EnQueue(struct queue_s *queue, struct bintree_s *bintree);
struct bintree_s *DeQueue(struct queue_s *queue);
int QueueIsEmpty(struct queue_s *queue);
struct queue_s *InitQueue(void);

#endif
