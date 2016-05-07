/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/queue.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "queue.h"
#include <stdlib.h>

/*
 * Create a queue node.
 */
static inline struct queueNode_s *CreateNode(struct ostree_s *ostree)
{
        struct queueNode_s *newNode = (struct queueNode_s *)malloc(sizeof(struct queueNode_s));
        newNode->ostree = ostree;
        newNode->prev = newNode->next = nullptr;

        return newNode;
}


/*
 * Initialize queue.
 */
struct queue_s *InitQueue(void)
{
        struct queue_s *queue = (struct queue_s *)malloc(sizeof(struct queue_s));
        queue->head = queue->tail = nullptr;
        queue->size = 0;

        return queue;
}

void EnQueue(struct queue_s *queue, struct ostree_s *ostree)
{
        struct queueNode_s *newNode = CreateNode(ostree);

        if (!QueueIsEmpty(queue)) {
                queue->tail->next = newNode;
                newNode->prev = queue->tail;
                queue->tail = newNode;
        } else {
                queue->head = queue->tail = newNode;
        }
        queue->size++;
}

struct ostree_s *DeQueue(struct queue_s *queue)
{
        if (!QueueIsEmpty(queue)) {
                struct queueNode_s *tempNode = queue->head;
                struct ostree_s *retPtr = tempNode->ostree;

                if (queue->size != 1) {
                        queue->head = queue->head->next;
                } else {
                        queue->head = queue->tail = nullptr;
                }
                queue->size--;
                free(tempNode);

                return retPtr;
        } else {
                return nullptr;
        }
}

bool QueueIsEmpty(struct queue_s *queue)
{
        return queue->size == 0;
}

/*
 * Delete the whole queue.
 */
void DeleteQueue(struct queue_s *queue)
{
        while (queue->head) {
                struct queueNode_s *tempPtr = queue->head;
                queue->head = queue->head->next;
                free(tempPtr);
        }
        free(queue);
}
