/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/queue.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "queue.h"

/*
 * Initialize queue.
 */
struct queue_s *InitQueue(void)
{
        struct queue_s *queue = (struct queue_s *)malloc(sizeof(struct queue_s));
        queue->head = queue->tail = NULL;
        queue->size = 0;

        return queue;
}

void EnQueue(struct queue_s *queue, struct bintree_s *bintree)
{
        struct queueNode_s *newNode = (struct queueNode_s *)malloc(sizeof(struct queueNode_s));
        newNode->bintree = bintree;
        newNode->prev = newNode->next = NULL;

        if (!QueueIsEmpty(queue)) {
                queue->tail->next = newNode;
                newNode->prev = queue->tail;
                queue->tail = newNode;
        } else {
                queue->head = queue->tail = newNode;
        }
        queue->size++;
}

struct bintree_s *DeQueue(struct queue_s *queue)
{
        if (!QueueIsEmpty(queue)) {
                struct queueNode_s *oldHead = queue->head;
                struct bintree_s *retPtr = oldHead->bintree;

                if (queue->size != 1) {
                        queue->head = queue->head->next;
                } else {
                        queue->head = queue->tail = NULL;
                }
                queue->size--;
                free(oldHead);

                return retPtr;
        } else {
                return NULL;
        }
}

/*
 * Query whether queue is empty.
 */
int QueueIsEmpty(struct queue_s *queue)
{
        return queue->size == 0;
}

/*
 * Delete the whole queue.
 */
void DeleteQueue(struct queue_s *queue)
{
        while (queue->head != NULL) {
                struct queueNode_s *tempPtr = queue->head;
                queue->head = queue->head->next;
                free(tempPtr);
        }
        free(queue);
}
