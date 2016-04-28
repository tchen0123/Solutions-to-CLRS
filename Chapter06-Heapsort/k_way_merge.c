/*
 * Solutions-to-CLRS/Chapter06-Heapsort/k_way_merge.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "k_way_merge.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

// linked list
struct list_s {
        int value;
        struct list_s *next;
        struct list_s *prev;
};

// min heap
struct minHeap_s {
        int value;
        int index; // record the array index
        int size;
};

/*
 * Create a list node.
 */
static inline struct list_s *CreateListNode(int num)
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

static struct list_s *CreateList(int n);
static void InsertionSort(struct list_s *listHead);
static void PrintList(struct list_s *listHead);

void KwayMerge(int k, int n)
{
        int i;
        struct list_s *listArray[k];

        // Create linked list
        for (i = 0; i < k; i++) {
                listArray[i] = CreateList(n);
        }
        // Insertion sort
        for (i = 0; i < k; i++) {
                InsertionSort(listArray[i]);
        }
        // Print the original list
        printf("The original list:\n");
        for (i = 0; i < k; i++) {
                printf("The %d-th list: ", i);
                PrintList(listArray[i]);
                printf("\n");
        }
}

/*
 * Create a linked list.
 */
static struct list_s *CreateList(int n)
{
        int i;
        struct list_s *listHead = NULL;

        for (i = 0; i < n; i++) {
                int num = rand() % (n * n); // create a random number
                struct list_s *newNode = CreateListNode(num);

                if (listHead) {
                        newNode->next = listHead;
                        listHead->prev = newNode;

                        listHead = newNode;
                } else {
                        listHead = newNode;
                }
        }

        return listHead;
}

/*
 * Insertion sort to linked list.
 */
static void InsertionSort(struct list_s *listHead)
{
        struct list_s *i;
        for (i = listHead->next; i != NULL; i = i->next) {
                struct list_s *j = i->prev;

                while (j != NULL && j->value > j->next->value) {
                        Swap(&(j->value), &(j->next->value));
                        j = j->prev;
                }
        }
}

/*
 * Print the linked list.
 */
static void PrintList(struct list_s *listHead)
{
        while (listHead != NULL) {
                printf("%d ", listHead->value);
                listHead = listHead->next;
        }
}
