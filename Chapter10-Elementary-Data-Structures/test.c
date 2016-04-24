/*
 * Solutions-to-CLRS/Chapter10-Elementary-Data-Structures/list.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "list.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static void RandomizeArray(int array[], int size);

int main(void)
{
        int size, i, select;

        printf("1.Linked list test\n");
        printf("2.Stack test\n");
        printf("3.Queue test\n");
        scanf("%d", &select);

        printf("How many integer numbers do you want to enter?\n");
        scanf("%d", &size);

        int array[size];
        for (i = 0; i < size; i++) {
                array[i] = i + 1;
        }

        RandomizeArray(array, size);

        printf("The input array:\n");
        for (i = 0; i < size; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");

        struct list_s *listHead = NULL;

        /* the initial stack capacity is 10 */
        struct stack_s *stack = InitStack(10);

        switch (select) {
        case 1:
                for (i = 0; i < size; i++) {
                        listHead = ListInsert(listHead, array[i]);
                }

                printf("List walk:\n");
                ListWalk(listHead);
                printf("\n\n");

                printf("List invert:\n");
                listHead = ListInvert(listHead);
                ListWalk(listHead);
                printf("\n\n");

                DeleteList(listHead);
                break;
        case 2:
                for (i = 0; i < size; i++) {
                        Push(stack, array[i]);
                }

                printf("\nStack walk:\n");
                StackWalk(stack);
                printf("\n\n");

                printf("Stack pop test:\n");
                for (i = 0; i < 5; i++) {
                        printf("pop: %d\n", Pop(stack));
                }
                printf("\n\n");

                DeleteStack(stack);
        }
        return 0;
}

/*
 * Randomize the array.
 */
static void RandomizeArray(int array[], int size)
{
        int i;
        for (i = 1; i < size; i++) {
                int tempIndex = rand() % i;
                Swap(&array[i], &array[tempIndex]);
        }
}

