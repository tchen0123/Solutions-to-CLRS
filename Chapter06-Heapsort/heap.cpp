#include "heap.h"


void maxHeapify(std::vector<int> &array, std::size_t size, std::size_t index)
{
        std::size_t left = LEFT(index), right = RIGHT(index);
        std::size_t largest;

        if (left < size && array[left] > array[index]) {
                largest = left;
        }
        else {
                largest = index;
        }
        if (right < size && array[right] > array[largest]) {
                largest = right;
        }

        if (largest != index) {
                std::swap(array[largest], array[index]);
                maxHeapify(array, size, largest);
        }
}

void buildMaxheap(std::vector<int> &array)
{
        for (int i = array.size(); i >= 0; --i) {
                maxHeapify(array, array.size(), i);
        }
}

void minHeapify(std::vector<int> &array, std::size_t size, std::size_t index)
{
        std::size_t left = LEFT(index), right = RIGHT(index);
        std::size_t least;

        if (left < size && array[left] < array[index]) {
                least = left;
        }
        else {
                least = index;
        }
        if (right < size && array[right] < array[least]) {
                least = right;
        }

        if (least != index) {
                std::swap(array[least], array[index]);
                minHeapify(array, size, least);
        }
}

void buildMinheap(std::vector<int> &array)
{
        for (int i = array.size() / 2; i >= 0; --i) {
                minHeapify(array, array.size(), i);
        }
}
