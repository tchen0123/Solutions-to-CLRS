#include "heapsort.h"
#include "heap.h"


void heapSort(std::vector<int> &array)
{
        buildMaxheap(array);

        std::size_t size = array.size();
        for (std::size_t i = size - 1; i != 0; --i) {
                std::swap(array[i], array[0]);
                maxHeapify(array, --size, 0);
        }
}
