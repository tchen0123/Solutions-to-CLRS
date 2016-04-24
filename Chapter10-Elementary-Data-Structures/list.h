/*
 * Solutions-to-CLRS/Chapter10-Elementary-Data-Structures/list.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * This routine is the implementation of double linek list.
 */

#ifndef __LIST_H_
#define __LIST_H_

struct list_s {
        int value;
        struct list_s *prev, *next;
};

struct list_s *ListInsert(struct list_s *listHead, int num);
struct list_s *ListDelete(struct list_s *listHead, int num);
struct list_s *ListSearch(struct list_s *listHead, int num);
void ListWalk(struct list_s *listHead);
void ListInvert(struct list_s *listHead);

#endif
