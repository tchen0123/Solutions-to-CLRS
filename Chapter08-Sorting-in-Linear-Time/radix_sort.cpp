#include "radix_sort.h"
#include <iostream>

#define SHIFT_AND_MASK(num, i) ((num >> (i * 8)) & 0x000000ff)


static inline int minimum(const std::vector<int> &array, const std::size_t index)
{
        int min = SHIFT_AND_MASK(array[0], index);
        for (std::size_t i = 1, size = array.size(); i != size; ++i) {
                if (min > SHIFT_AND_MASK(array[i], index)) {
                        min = SHIFT_AND_MASK(array[i], index);
                }
        }
        return min;
}

static inline int maximum(const std::vector<int> &array, const std::size_t index)
{
        int max = SHIFT_AND_MASK(array[0], index);
        for (std::size_t i = 1, size = array.size(); i != size; ++i) {
                if (max < SHIFT_AND_MASK(array[i], index)) {
                        max = SHIFT_AND_MASK(array[i], index);
                }
        }
        return max;
}


static void countingSort(const std::vector<int> &src, std::vector<int> &dest, const std::size_t index)
{
        int min = minimum(src, index);
        int max = maximum(src, index);
        std::size_t len = max - min + 1;

        std::vector<int> count(len, 0);
        for (std::size_t i = 0, size = src.size(); i != size; ++i) {
                ++count[SHIFT_AND_MASK(src[i], index) - min];
        }
        for (std::size_t i = 1; i != len; ++i) {
                count[i] += count[i - 1];
        }

        for (int i = src.size() - 1; i >= 0; --i) {
                dest[count[SHIFT_AND_MASK(src[i], index) -min] - 1] = src[i];
                --count[SHIFT_AND_MASK(src[i], index) - min];
        }
}

void radixSort(std::vector<int> &src, std::vector<int> &dest)
{
        std::size_t cnt = sizeof(int);
        for (std::size_t i = 0; i != cnt; ++i) {
                countingSort(src, dest, i);

                src = dest;
        }
}
