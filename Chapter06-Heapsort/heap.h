#ifndef HEAP_H
#define HEAP_H

#include <vector>

#define PARENT(i)  (i - 1) / 2
#define LEFT(i)    i * 2 + 1
#define RIGHT(i)   i * 2 + 2


void maxHeapify(std::vector<int> &array, std::size_t size, std::size_t index);
void buildMaxheap(std::vector<int> &array);
void minHeapify(std::vector<int> &array, std::size_t size, std::size_t index);
void buildMinheap(std::vector<int> &array);

#endif
