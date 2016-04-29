/*
 * Solutions-to-CLRS/Chapter06-Heapsort/Kway_merge.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the implementation of K-way merge using priority queue.
 */

#include "Kway_merge.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


#define PARENT(i)    (i - 1) / 2
#define LEFT(i)      i * 2 + 1
#define RIGHT(i)     i * 2 + 2


// linked list
struct list_s {
        int value;
        struct list_s *prev;
        struct list_s *next;
};

struct heapNode_s {
        int value;
        int index;
};
struct heap_s {
        struct heapNode_s array[HEAP_MAX_SIZE];
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

/*
 * Swap.
 */
static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}


static struct list_s *CreateList(int n);
static void InsertionSort(struct list_s *listHead);
static void PrintList(struct list_s *listHead);
static void ListMerge(int array[], int arraySize, struct list_s *listArray[], int k);
static struct list_s *ListLinkToNext(struct list_s *listHead);

static void MinHeapify(struct heap_s *heap, int index);
static void BuildMinHeap(struct heap_s *heap);
static void MinHeapDeleteMin(struct heap_s *heap);
static int MinHeapIsEmpty(struct heap_s *heap);
static struct heap_s *InitMinHeap(int k);


/*
 * Yeah, yeah, it's ugly, but I cannot find how to do this correctly
 * and this seems to work. I will try to use other algorithms called
 * Lose Tree.
 */
void KwayMerge(int k, int n)
{
        int i;
        struct list_s *listArray[k];

        // Create list
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

        int arraySize = k * n;
        int array[arraySize];

        // K-way Merge!
        ListMerge(array, arraySize, listArray, k);

        printf("After K-way merging:\n");
        for (i = 0; i < arraySize; i++) {
                printf("%d ", array[i]);
        }
        printf("\n");

        // Delete the linked lists
        for (i = 0; i < k; i++) {
                struct list_s *tempPtr = listArray[i];
                while (listArray[i] != NULL) {
                        tempPtr = listArray[i];
                        listArray[i] = listArray[i]->next;
                        free(tempPtr);
                }
        }
}


static void ListMerge(int array[], int arraySize, struct list_s *listArray[], int k)
{
        int i;

        struct heap_s *heap = InitMinHeap(k);

        // First build min heap
        for (i = 0; i < k; i++) {
                heap->array[i].value = listArray[i]->value;
                heap->array[i].index = i;
        }
        BuildMinHeap(heap);

        int cnt = -1; // record array index

        while (!MinHeapIsEmpty(heap)) {
                cnt++;
                array[cnt] = heap->array[0].value;

                // link the list to the next node
                int index = heap->array[0].index;
                listArray[index] = ListLinkToNext(listArray[index]);

                if (listArray[index]) {
                        heap->array[0].value = listArray[index]->value;
                        heap->array[0].index = index;

                        MinHeapify(heap, 0);
                } else {
                        MinHeapDeleteMin(heap);
                }
        }

        // Delete the heap
        free(heap);
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

/*
 * Maintain the min heap property.
 */
static void MinHeapify(struct heap_s *heap, int index)
{
        int least;

        if (LEFT(index) < heap->size && heap->array[LEFT(index)].value < heap->array[index].value) {
                least = LEFT(index);
        } else {
                least = index;
        }
        if (RIGHT(index) < heap->size && heap->array[RIGHT(index)].value < heap->array[least].value) {
                least = RIGHT(index);
        }

        if (least != index) {
                Swap(&(heap->array[least].value), &(heap->array[index].value));
                Swap(&(heap->array[least].index), &(heap->array[index].index));

                MinHeapify(heap, least);
        }
}

/*
 * Build a min heap.
 */
static void BuildMinHeap(struct heap_s *heap)
{
        int i;
        for (i = heap->size / 2; i >= 0; i--) {
                MinHeapify(heap, i);
        }
}

/*
 * Delete the min.
 */
static void MinHeapDeleteMin(struct heap_s *heap)
{
        heap->array[0] = heap->array[heap->size - 1];
        heap->size--;
        MinHeapify(heap, 0);
}

/*
 * Query whether the min heap is empty.
 */
static int MinHeapIsEmpty(struct heap_s *heap)
{
        return heap->size == 0;
}

/*
 * Initialize min heap.
 */
static struct heap_s *InitMinHeap(int k)
{
        struct heap_s *heap = (struct heap_s *)malloc(sizeof(struct heap_s));
        heap->size = k;

        return heap;
}

/*
 * Link to list head node to the next node.
 */
static struct list_s *ListLinkToNext(struct list_s *listHead)
{
        struct list_s *tempPtr = listHead;
        listHead = listHead->next;
        if (listHead) {
                listHead->prev = NULL;
        }
        free(tempPtr);

        return listHead;
}
