/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/pre_tree_walk.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the implementation of preorder and inorder tree walk stack.
 */

#include "pre_tree_walk.h"
#include <stdlib.h>

/*
 * Initialize preorder walk stack.
 */
struct preWalk_s *InitPreWalk(void)
{
        struct preWalk_s *stack = (struct preWalk_s *)malloc(sizeof(struct preWalk_s));
        stack->top = NULL;
        stack->size = 0;

        return stack;
}

/*
 * Preorder and inorder tree walk stack push
 */
void PreWalkPush(struct preWalk_s *stack, struct bintree_s *bintree)
{
        struct preWalkNode_s *newNode = (struct preWalkNode_s *)malloc(sizeof(struct preWalkNode_s));
        newNode->bintree = bintree;
        newNode->prev = newNode->next = NULL;

        if (!PreWalkIsEmpty(stack)) {
                stack->top->next = newNode;
                newNode->prev = stack->top;
                stack->top = stack->top->next;
        } else {
                stack->top = newNode;
        }
        stack->size++;
}

/*
 * Preorder walk stack pop.
 */
struct bintree_s *PreWalkPop(struct preWalk_s *stack)
{
        if (!PreWalkIsEmpty(stack)) {
                struct preWalkNode_s *tempPtr = stack->top;
                struct bintree_s *retPtr = tempPtr->bintree;

                if (stack->size != 1) {
                        stack->top = stack->top->prev;
                        stack->top->next = NULL;
                } else {
                        stack->top = NULL;
                }
                stack->size--;
                free(tempPtr);

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
 * Delete the whole stack.
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
