#include "insertion_sort.h"


void insertionSort(std::vector<int> &array)
{
        const auto size = array.size();
        for (std::size_t i = 1; i != size; ++i) {
                const int key = array[i];
                int j = i - 1;
                while (j >= 0 && array[j] > key) {
                        array[j + 1] = array[j];
                        --j;
                }
                array[j + 1] = key;
        }
}
