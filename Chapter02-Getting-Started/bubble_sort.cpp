#include "bubble_sort.h"

void bubbleSort(std::vector<int> &array)
{
        const auto size = array.size();
        for (std::size_t i = 0; i != size; ++i) {
                for (std::size_t j = size - 1; j != i; --j) {
                        if (array[j] < array[j - 1]) {
                                std::swap(array[j], array[j - 1]);
                        }
                }
        }
}
