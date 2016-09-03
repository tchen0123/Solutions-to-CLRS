#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>

#define PARENT(i)   (i - 1) / 2
#define LEFT(i)      i * 2 + 1
#define RIGHT(i)     i * 2 + 2


struct Node {
        int value;
        std::size_t index;
};

struct Minheap {
        std::vector<struct Node> array;
        std::size_t size;
};

bool heapIsEmpty(struct Minheap &heap);
void minHeapify(struct Minheap &heap, std::size_t index);
void buildMinheap(struct Minheap &heap);

#endif
