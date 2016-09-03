#ifndef LIST_H
#define LIST_H

#include <vector>

struct List {
        int value;
        struct List *next;
};

struct List *createList(std::size_t n);

#endif
