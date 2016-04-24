/*
 * Solutions-to-CLRS/Chapter10-Elementary-Data-Structures/list.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the implementation of queue.
 * Using array.
 */

#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <stdlib.h>

struct queue_s {
        int *array;
        int head;
        int tail;
        size_t size;
        size_t capacity;
};

struct queue_s *InitQueue(size_t capacity);
void EnQueue(struct queue_s *queue, int num);
int DeQueue(struct queue_s *queue);
int QueueIsEmpty(struct queue_s *queue);
int QueueIsFull(struct queue_s *queue);
void DeleteQueue(struct queue_s *queue);
void QueueWalk(struct queue_s *queue);

#endif
