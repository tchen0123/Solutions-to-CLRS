/*
 * Solutions-to-CLRS/Chapter10-Elementary-Data-Structures/stack.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the inplementation of stack.
 * Using pointer.
 */

#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Creat a new stack node.
 */
static inline struct stackNode_s *CreateNode(int num)
{
        struct stackNode_s *newNode = (struct stackNode_s *)malloc(sizeof(struct stackNode_s));
        newNode->value = num;
        newNode->prev = newNode->next = NULL;

        return newNode;
}

/*
 * Stack push operation.
 */
void Push(struct stack_s *stack, int num)
{
        if (!StackIsFull(stack)) {
                struct stackNode_s *newNode = CreateNode(num);

                if (stack->size != 0) {
                        stack->top->next = newNode;
                        newNode->prev = stack->top;

                        stack->top = stack->top->next;
                } else {
                        stack->top = newNode;
                }

                stack->size++;
        } else {
                fprintf(stderr, "Stack is full!\n");
        }
}

/*
 * Stack pop operation.
 */
int Pop(struct stack_s *stack)
{
        if (!StackIsEmpty(stack)) {
                int retValue = stack->top->value;

                if (stack->size != 1) {
                        struct stackNode_s *tempPtr = stack->top->prev;
                        free(stack->top);
                        stack->top = tempPtr;
                } else {
                        free(stack->top);
                        stack->top = NULL;
                }
                stack->size--;

                return retValue;
        } else {
                fprintf(stderr, "Stack is empty!");
                return -1;
        }
}

/*
 * Query whether stack is empty.
 */
int StackIsEmpty(struct stack_s *stack)
{
        return stack->size == 0;
}

/*
 * Query whether stack is full.
 */
int StackIsFull(struct stack_s *stack)
{
        return stack->size == stack->capacity;
}

/*
 * Initialize the stack.
 */
struct stack_s *InitStack(int capacity)
{
        struct stack_s *stack = (struct stack_s *)malloc(sizeof(struct stack_s));
        stack->capacity = capacity;
        stack->size = 0;
        stack->top = NULL;

        return stack;
}

/*
 * Stack walk.
 */
void StackWalk(struct stack_s *stack)
{
        struct stackNode_s *tempPtr = stack->top;
        while (tempPtr != NULL) {
                printf("%d ", tempPtr->value);
                tempPtr = tempPtr->prev;
        }
}

/*
 * Delete the whole stack.
 */
void DeleteStack(struct stack_s *stack)
{
        while (stack->top != NULL) {
                struct stackNode_s *tempPtr = stack->top;
                stack->top = stack->top->prev;
                free(tempPtr);
        }

        free(stack);
}
