#include "quicksort.h"
#include <cstdlib>

static std::size_t randomPartition(std::vector<int> &array, std::size_t low, std::size_t high)
{
        // 產生一個隨機下標，再與array[high]交換
        std::size_t temp = std::rand() % (high - low + 1) + low;
        std::swap(array[temp], array[high]);

        int key = array[high];
        int less = low - 1;
        for (std::size_t larger = low; larger != high; ++larger) {
                if (array[larger] <= key) {
                        ++less;
                        std::swap(array[less], array[larger]);
                }
        }
        ++less;
        std::swap(array[less], array[high]);

        return less;
}

void quickSort(std::vector<int> &array, std::size_t low, std::size_t high)
{
        if (low < high) {
                std::size_t q = randomPartition(array, low, high);
                quickSort(array, low, q - 1);
                quickSort(array, q + 1, high);
        }
}
