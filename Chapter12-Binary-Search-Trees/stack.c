/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/stack.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "stack.h"
#include <stdlib.h>

/*
 * Create a new stack node.
 */
static inline struct stackNode_s *CreateNode(struct bintree_s *bintree)
{
        struct stackNode_s *newNode = (struct stackNode_s *)malloc(sizeof(struct stackNode_s));
        newNode->bintree = bintree;
        newNode->prev = newNode->next = NULL;

        return newNode;
}

/*
 * Initialize stack.
 */
struct stack_s *InitStack(void)
{
        struct stack_s *stack = (struct stack_s *)malloc(sizeof(struct stack_s));
        stack->top = NULL;
        stack->size = 0;

        return stack;
}

/*
 * Stack push operation.
 */
void Push(struct stack_s *stack, struct bintree_s *bintree)
{
        struct stackNode_s *newNode = CreateNode(bintree);

        if (!StackIsEmpty(stack)) {
                stack->top->next = newNode;
                newNode->prev = stack->top;
                stack->top = newNode;
        } else {
                stack->top = newNode;
        }
        stack->size++;
}

/*
 * Stack pop operation.
 */
struct bintree_s *Pop(struct stack_s *stack)
{
        if (!StackIsEmpty(stack)) {
                struct stackNode_s *tempPtr = stack->top;
                struct bintree_s *retPtr = tempPtr->bintree;
                stack->top = stack->top->prev;

                free(tempPtr);
                stack->size--;

                return retPtr;
        } else {
                return NULL;
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
 * Delete the whole stack.
 */
void DeleteStack(struct stack_s *stack)
{
        int i, size;

        size = stack->size;
        for (i = 0; i < size; i++) {
                struct stackNode_s *tempPtr = stack->top;
                stack->top = stack->top->prev;
                free(tempPtr);
        }

        free(stack);
}
