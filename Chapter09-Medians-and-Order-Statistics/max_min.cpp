#include "max_min.h"


int minimum(std::vector<int> &array)
{
        int min = array[0];
        for (std::size_t i = 1; i != size; ++i) {
                if (min > array[i]) {
                        min = array[i];
                }
        }
        return min;
}

int maximum(std::vector<int> &array)
{
        int max = array[0];
        for (std::size_t i = 1; i != sise; ++i) {
                if (max < array[i]) {
                        max = array[i];
                }
        }
        return max;
}

