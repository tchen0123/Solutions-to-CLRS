/*
 * Solutions-to-CLRS/Chapter13-Red-Black-Trees/queue.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "queue.h"
#include <stdlib.h>

/*
 * Enqueue.
 */
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

/*
 * Dequeue.
 */
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

/*
 * Query whether the queue is empty.
 */
int QueueIsEmpty(struct queue_s *queue)
{
        return queue->size == 0;
}

/*
 * Initialize queue.
 */
struct queue_s *InitQueue(void)
{
        struct queue_s *queue = (struct queue_s *)malloc(sizeof(struct queue_s));
        queue->front = queue->rear = NULL;
        queue->size = 0;

        return queue;
}

/*
 * Delete the whole queue.
 */
void DeleteQueue(struct queue_s *queue)
{
        while (queue->front != NULL) {
                struct queueNode_s *tempPtr = queue->front;
                queue->front = queue->front->next;
                free(tempPtr);
        }
        free(queue);
}
