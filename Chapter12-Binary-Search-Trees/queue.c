/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/queue.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "queue.h"

/*
 * Enqueue.
 */
void EnQueue(struct queue_s *queue, struct bintree_s *bintree)
{
        struct queueNode_s *newNode = (struct queueNode_s *)malloc(sizeof(struct queueNode_s));
        newNode->bintree = bintree;
        newNode->next = NULL;

        if (!QueueIsEmpty(queue)) {
                queue->rear->next = newNode;
                queue->rear = queue->rear->next;
        } else {
                queue->front = queue->rear = newNode;
        }
        queue->size++;
}

/*
 * Dequeue.
 */
struct bintree_s *DeQueue(struct queue_s *queue)
{
        if (!QueueIsEmpty(queue)) {
                struct queueNode_s *oldFront = queue->front;
                struct bintree_s *retPtr = oldFront->bintree;

                if (queue->size != 1) {
                        queue->front = queue->front->next;
                } else {
                        queue->front = queue->rear = NULL;
                }
                free(oldFront);
                queue->size--;

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
 * Initialize the queue.
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
