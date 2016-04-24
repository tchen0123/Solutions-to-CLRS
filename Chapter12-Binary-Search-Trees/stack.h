/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/stack.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __STACK_H_
#define __STACK_H_

#include <stdlib.h>
#include "bintree.h"

struct stackNode_s {
        struct bintree_s *bintree;
        struct stackNode_s *prev;
        struct stackNode_s *next;
};

struct stack_s {
        struct stackNode_s *top;
        size_t size;
};

struct stack_s *InitStack(void);
void Push(struct stack_s *stack, struct bintree_s *bintree);
struct bintree_s *Pop(struct stack_s *stack);
int StackIsEmpty(struct stack_s *stack);

#endif
