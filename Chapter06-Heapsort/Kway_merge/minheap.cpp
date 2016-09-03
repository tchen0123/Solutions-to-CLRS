#include "minheap.h"


void minHeapify(struct Minheap &heap, std::size_t index)
{
        std::size_t left = LEFT(index), right = RIGHT(index), least;

        if (left < heap.size && heap.array[left].value < heap.array[index].value) {
                least = left;
        }
        else {
                least = index;
        }
        if (right < heap.size && heap.array[right].value < heap.array[least].value) {
                least = right;
        }

        if (least != index) {
                std::swap(heap.array[least], heap.array[index]);
                minHeapify(heap, least);
        }
}

void buildMinheap(struct Minheap &heap)
{
        for (int i = heap.size / 2; i >= 0; --i) {
                minHeapify(heap, i);
        }
}

bool heapIsEmpty(struct Minheap &heap)
{
        return heap.size == 0;
}
