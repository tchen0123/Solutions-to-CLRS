#include "select.h"
#include <cstdlib>

std::size_t partition(std::vector<int> &array, std::size_t low, std::size_t high)
{
        std::size_t tempIndex = std::rand() % (high - low + 1) + low;
        std::swap(array[high], array[tempIndex]);

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

int select(std::vector<int> array, std::size_t low, std::size_t high, std::size_t K)
{
        std::size_t pivot = partition(array, low, high);
        std::size_t len = pivot - low + 1;

        if (len == K) {
                return pivot;
        }
        else if (K < len) {
                return select(array, low, pivot - 1, K);
        }
        else {
                return select(array, pivot + 1, high, K - len);
        }
}
