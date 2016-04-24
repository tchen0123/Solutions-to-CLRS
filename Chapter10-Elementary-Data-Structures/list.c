/*
 * Solutions-to-CLRS/Chapter10-Elementary-Data-Structures/list.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the implementation of single linek list.
 */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Create a new list node.
 */
static inline struct list_s *CreateNode(int num)
{
        struct list_s *newNode = (struct list_s *)malloc(sizeof(struct list_s));
        newNode->value = num;
        newNode->prev = newNode->next = NULL;

        return newNode;
}

/*
 * Insert a new node into the list.
 * First in last out.
 */
struct list_s *ListInsert(struct list_s *listHead, int num)
{
        struct list_s *newNode = CreateNode(num);

        if (listHead) {
                newNode->next = listHead;
                listHead->prev = newNode;
                listHead = newNode;
        } else {
                listHead = newNode;
        }

        return listHead;
}

/*
 * List delete opration.
 */
struct list_s *ListDelete(struct list_s *listHead, int num)
{
        struct list_s *targetPtr = ListSearch(listHead, num);

        if (targetPtr) {
                if (targetPtr != listHead) {
                        targetPtr->prev->next = targetPtr->next;
                        if (targetPtr->next) {
                                targetPtr->next->prev = targetPtr->prev;
                        }
                } else {
                        listHead = listHead->next;
                        listHead->prev = NULL;
                }
                free(targetPtr);
        }

        return listHead;
}

/*
 * Search a node.
 */
struct list_s *ListSearch(struct list_s *listHead, int num)
{
        while (listHead != NULL && listHead->value != num) {
                listHead = listHead->next;
        }

        return listHead;
}

/*
 * List Walk.
 */
void ListWalk(struct list_s *listHead)
{
        while (listHead != NULL) {
                printf("%d ", listHead->value);
                listHead = listHead->next;
        }
}

/*
 * Invert the list.
 */
void ListInvert(struct list_s *listHead)
{
        struct list_s *sentinelHead = (struct list_s *)malloc(sizeof(struct list_s));
        sentinelHead->next = listHead;

        struct list_s *tempPtr;
        while (listHead->next != NULL) {
                tempPtr = listHead->next;

                listHead->next = tempPtr->next;
                if (listHead->next) {
                        listHead->next->prev = listHead;
                }

                tempPtr->next = sentinelHead->next;
                sentinelHead->next = tempPtr;
        }

        listHead = sentinelHead->next;
        listHead->prev = NULL;

        ListWalk(listHead);
}
