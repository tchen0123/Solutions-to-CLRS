/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/invltree_queue.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the implementation of invltree walk queue.
 */

#include "invltree_queue.h"
#include <stdlib.h>

/*
 * Create a new node.
 */
static inline struct invlqueueNode_s *CreateNode(struct invlTree_s *invlTree)
{
        struct invlqueueNode_s *newNode = (struct invlqueueNode_s *)malloc(sizeof(struct invlqueueNode_s));
        newNode->invlTree = invlTree;
        newNode->next = nullptr;

        return newNode;
}

/*
 * Initialize.
 */
struct invlqueue_s *InitInvlqueue(void)
{
        struct invlqueue_s *queue = (struct invlqueue_s *)malloc(sizeof(struct invlqueue_s));
        queue->head = queue->tail = nullptr;
        queue->size = 0;

        return queue;
}

void EnInvlqueue(struct invlqueue_s *queue, struct invlTree_s *invlTree)
{
        struct invlqueueNode_s *newNode = CreateNode(invlTree);

        if (!InvlqueueIsEmpty(queue)) {
                queue->tail->next = newNode;
                queue->tail = newNode;
        } else {
                queue->head = queue->tail = newNode;
        }
        queue->size++;
}

struct invlTree_s *DeInvlqueue(struct invlqueue_s *queue)
{
        if (!InvlqueueIsEmpty(queue)) {
                struct invlqueueNode_s *tempNode = queue->head;
                struct invlTree_s *retPtr = tempNode->invlTree;

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

bool InvlqueueIsEmpty(struct invlqueue_s *queue)
{
        return queue->size == 0;
}

/*
 * Delete the whole queue.
 */
void DeleteInvlqueue(struct invlqueue_s *queue)
{
        while (queue->head) {
                struct invlqueueNode_s *tempPtr = queue->head;
                queue->head = queue->head->next;
                free(tempPtr);
        }
        free(queue);
}
