/*
 * Solutions-to-CLRS/Chapter10-Elementary-Data-Structures/list.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the implementation of queue.
 * Using array.
 */

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Initialize queue.
 */
struct queue_s *InitQueue(int capacity)
{
        struct queue_s *queue = (struct queue_s *)malloc(sizeof(struct queue_s));
        queue->capacity = capacity;
        queue->head = queue->tail = -1;
        queue->size = 0;
        queue->array = (int *)malloc(sizeof(int) * capacity);

        return queue;
}

/*
 * Enqueue operation.
 */
void EnQueue(struct queue_s *queue, int num)
{
        if (!QueueIsFull(queue)) {
                if (queue->tail != queue->capacity - 1) {
                        queue->tail++;
                        if (queue->size == 0) {
                                queue->head = queue->tail;
                        }
                } else { // case: the queue tail arrives the end of array
                        queue->tail = 0;
                }
                queue->array[queue->tail] = num;
                queue->size++;
        } else {
                fprintf(stderr, "Queue is full!\n");
        }
}

/*
 * Dequeue operation.
 */
int DeQueue(struct queue_s *queue)
{
        if (!QueueIsEmpty(queue)) {
                int retValue = queue->array[queue->head];

                if (queue->size != 1) {
                        if (queue->head != queue->capacity - 1) {
                                queue->head++;
                        } else { // case: the queue tail arrives the end of array
                                queue->head = 0;
                        }
                } else {
                        queue->head = queue->tail = -1;
                }
                queue->size--;

                return retValue;
        } else {
                fprintf(stderr, "Queue is empty!\n");
                return -1;
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
 * Query whether queue is full.
 */
int QueueIsFull(struct queue_s *queue)
{
        return queue->size == queue->capacity;
}

/*
 * Delete the whole queue.
 */
void DeleteQueue(struct queue_s *queue)
{
        free(queue->array);
        free(queue);
}

/*
 * Queue walk.
 */
void QueueWalk(struct queue_s *queue)
{
        int i;

        if (queue->head <= queue->tail) {
                for (i = queue->head; i <= queue->tail; i++) {
                        printf("%d ", queue->array[i]);
                }
        } else {
                for (i = queue->head; i < queue->capacity; i++) {
                        printf("%d ", queue->array[i]);
                }
                for (i = 0; i <= queue->tail; i++) {
                        printf("%d ", queue->array[i]);
                }
        }
}
