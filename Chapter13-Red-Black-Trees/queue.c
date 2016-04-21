/*
 * Solutions-to-CLRS/Chapter13-Red-Black-Trees/queue.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "queue.h"
#include <stdlib.h>

void EnQueue(struct queue_s *queue, struct rbtree_s *rbtree)
{
        struct queueNode_s *newNode = (struct queueNode_s *)malloc(sizeof(struct queueNode_s));
        newNode->rbtree = rbtree;
        newNode->next = NULL;

        if (!QueueIsEmpty(queue)) {
                queue->rear->next = newNode;
                queue->rear = newNode;
        } else {
                queue->front = queue->rear = newNode;
        }
        queue->size++;
}

struct rbtree_s *DeQueue(struct queue_s *queue)
{
        struct queueNode_s *oldFront = queue->front;
        struct rbtree_s *retPtr = oldFront->rbtree;

        if (!QueueIsEmpty(queue)) {
                if (queue->size != 1) {
                        queue->front = queue->front->next;
                } else {
                        queue->front = queue->rear = NULL;
                }
                queue->size--;
                free(oldFront);

                return retPtr;
        } else {
                return NULL;
        }
}

int QueueIsEmpty(struct queue_s *queue)
{
        return queue->size == 0;
}

struct queue_s *InitQueue(void)
{
        struct queue_s *queue = (struct queue_s *)malloc(sizeof(struct queue_s));
        queue->front = queue->rear = NULL;
        queue->size = 0;

        return queue;
}
