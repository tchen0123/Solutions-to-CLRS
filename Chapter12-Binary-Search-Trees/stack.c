/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/stack.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "stack.h"

/*
 * Initialize preorder and inorder tree walk stack.
 */
struct preWalk_s *InitPreWalk(void)
{
        struct preWalk_s *stack = (struct preWalk_s *)malloc(sizeof(struct preWalk_s));
        stack->top = NULL;
        stack->size = 0;

        return stack;
}

/*
 * Preorder and inorder tree walk stack.
 */
void PreWalkPush(struct preWalk_s *stack, struct bintree_s *bintree)
{
        struct preWalkNode_s *newnode = (struct preWalkNode_s *)malloc(sizeof(struct preWalkNode_s));
        newnode->bintree = bintree;
        newnode->prev = newnode->next = NULL;

        if (!PreWalkIsEmpty(stack)) {
                stack->top->next = newnode;
                newnode->prev = stack->top;
                stack->top = newnode;
        } else {
                stack->top = newnode;
        }
        stack->size++;
}

/*
 * Preorder and inorder tree walk stack pop.
 */
struct bintree_s *PreWalkPop(struct preWalk_s *stack)
{
        if (!PreWalkIsEmpty(stack)) {
                struct preWalkNode_s *tempNode = stack->top;
                struct bintree_s *retPtr = tempNode->bintree;

                if (stack->size != 1) {
                        stack->top = stack->top->prev;
                        stack->top->next = NULL;
                } else {
                        stack->top = NULL;
                }
                stack->size--;
                free(tempNode);

                return retPtr;
        } else {
                return NULL;
        }
}

/*
 * Query whether stack is empty.
 */
int PreWalkIsEmpty(struct preWalk_s *stack)
{
        return stack->size == 0;
}

/*
 * Delete the whole preorder and inorder tree walk stack.
 */
void DeletePreWalk(struct preWalk_s *stack)
{
        while (stack->top != NULL) {
                struct preWalkNode_s *tempPtr = stack->top;
                stack->top = stack->top->prev;
                free(tempPtr);
        }
        free(stack);
}

/*
 * initialize post tree walk stack.
 */
struct postWalk_s *InitPostWalk(void)
{
        struct postWalk_s *stack = (struct postWalk_s *)malloc(sizeof(struct postWalk_s));
        stack->top = NULL;
        stack->size = 0;

        return stack;
}

/*
 * Post tree walk push.
 */
void PostWalkPush(struct postWalk_s *stack, struct bintree_s *bintree, bool isFirst)
{
        struct postWalkNode_s *newNode = (struct postWalkNode_s *)malloc(sizeof(struct postWalkNode_s));
        newNode->bintree = bintree;
        newNode->isFirst = isFirst;
        newNode->prev = newNode->next = NULL;

        if (!PostWalkIsEmpty(stack)) {
                stack->top->next = newNode;
                newNode->prev = stack->top;
                stack->top = newNode;
        } else {
                stack->top = newNode;
        }
        stack->size++;
}

/*
 * Post tree walk pop.
 */
struct postWalkNode_s *PostWalkPop(struct postWalk_s *stack)
{
        if (!PostWalkIsEmpty(stack)) {
                struct postWalkNode_s *retPtr = stack->top;

                if (stack->size != 1) {
                        stack->top = stack->top->prev;
                        stack->top->next = NULL;
                } else {
                        stack->top = NULL;
                }
                stack->size--;

                return retPtr;
        } else {
                return NULL;
        }
}

/*
 * Query whether stack is empty.
 */
int PostWalkIsEmpty(struct postWalk_s *stack)
{
        return stack->size == 0;
}

/*
 * Delete the whole stack.
 */
void DeletePostWalk(struct postWalk_s *stack)
{
        while (stack->top != NULL) {
                struct postWalkNode_s *tempPtr = stack->top;
                stack->top = stack->top->next;
                free(tempPtr);
        }
        free(stack);
}
