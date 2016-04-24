/*
 * Solutions-to-CLRS/Chapter10-Elementary-Data-Structures/list.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the inplementation of stack.
 * Using pointer.
 */

#ifndef __STACK_H_
#define __STACK_H_

#include <stdlib.h>

struct stackNode_s {
        int value;
        struct stackNode_s *prev, *next;
};

struct stack_s {
        struct stackNode_s *top;
        size_t size;
        size_t capacity;
};

struct stack_s *InitStack(int capacity);
void Push(struct stack_s *stack, int num);
int Pop(struct stack_s *stack);
int StackIsEmpty(struct stack_s *stack);
int StackIsFull(struct stack_s *stack);
void StackWalk(struct stack_s *stack);
void DeleteStack(struct stack_s *stack);

#endif
