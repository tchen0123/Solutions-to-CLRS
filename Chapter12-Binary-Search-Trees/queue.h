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
        struct queueNode_s *prev, *next;
};

struct queue_s {
        struct queueNode_s *head, *tail;
        size_t size;
};

struct queue_s *InitQueue(void);
void EnQueue(struct queue_s *queue, struct bintree_s *bintree);
struct bintree_s *DeQueue(struct queue_s *queue);
int QueueIsEmpty(struct queue_s *queue);
void DeleteQueue(struct queue_s *queue);

#endif
