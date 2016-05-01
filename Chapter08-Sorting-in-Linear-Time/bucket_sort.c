/*
 * Solutions-to-CLRS/Chapter08-Sorting-in-Linear-Time/bucket_sort.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "bucket_sort.h"
#include <stdlib.h>
#include <memory.h>

struct list_s {
        int value;
        struct list_s *prev;
        struct list_s *next;
};

static inline int Minimum(int array[], const int size)
{
        int i, min;

        min = array[0];
        for (i = 1; i < size; i++) {
                if (array[i] < min) {
                        min = array[i];
                }
        }

        return min;
}

static inline int Maximum(int array[], const int size)
{
        int i, max;

        max = array[0];
        for (i = 1; i < size; i++) {
                if (array[i] > max) {
                        max = array[i];
                }
        }

        return max;
}

/*
 * Create a new list node.
 */
static inline struct list_s *CreateListNode(const int num)
{
        struct list_s *newNode = (struct list_s *)malloc(sizeof(struct list_s));
        newNode->value = num;
        newNode->prev = newNode->next = NULL;

        return newNode;
}

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static struct list_s *ListInsert(struct list_s *listHead, const int num);
static struct list_s *ListSort(struct list_s *listHead);

void BucketSort(int array[], const int arraySize)
{
        int i, max, min, len;

        max = Maximum(array, arraySize);
        min = Minimum(array, arraySize);
        len = max - min + 1;

        struct list_s *bucket[arraySize];
        for (i = 0; i < arraySize; i++) {
                bucket[i] = NULL;
        }

        // Insert to bucket
        for (i = 0; i < arraySize; i++) {
                int index = (array[i] - min) / len * arraySize;
                bucket[index] = ListInsert(bucket[index], array[i]);
        }

        // Sort
        for (i = 0; i < arraySize; i++) {
                if (bucket[i]) {
                        bucket[i] = ListSort(bucket[i]);
                }
        }

        // Link each bucket
        int count = 0;
        for (i = 0; i < arraySize; i++) {
                while (bucket[i]) {
                        array[count] = bucket[i]->value;
                        bucket[i] = bucket[i]->next;
                        count++;
                }
        }
}

/*
 * List sort.
 */
static struct list_s *ListSort(struct list_s *listHead)
{
        struct list_s *i;
        for (i = listHead->next; i != NULL; i = i->next) {
                struct list_s *j = i->prev;

                while (j != NULL && j->value > j->next->value) {
                        Swap(&(j->value), &(j->next->value));

                        j = j->prev;
                }
        }

        return listHead;
}

/*
 * Insert a number to the list.
 */
static struct list_s *ListInsert(struct list_s *listHead, const int num)
{
        struct list_s *newnode = CreateListNode(num);

        if (listHead) {
                newnode->next = listHead;
                listHead->prev = newnode;
                listHead = newnode;
        } else {
                listHead = newnode;
        }

        return listHead;
}
