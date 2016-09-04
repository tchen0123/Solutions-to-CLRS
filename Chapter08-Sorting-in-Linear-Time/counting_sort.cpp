#include "counting_sort.h"


static inline int minimum(std::vector<int> &array)
{
        int min = array[0];
        for (std::size_t i = 1, size = array.size(); i != size; ++i) {
                if (min > array[i]) {
                        min = array[i];
                }
        }
        return min;
}

static inline int maximum(std::vector<int> &array)
{
        int max = array[0];
        for (std::size_t i = 1, size = array.size(); i != size; ++i) {
                if (max < array[i]) {
                        max = array[i];
                }
        }
        return max;
}


void countingSort(std::vector<int> &src, std::vector<int> &dest)
{
        // 求出數組src的最大最小值之差
        // 利用與最小值的偏離
        int min = minimum(src);
        int max = maximum(src);
        std::size_t len = max - min + 1;

        //count[i]保留着等於i的元素的個數
        std::vector<std::size_t> count(len, 0);
        for (std::size_t i = 0, size = src.size(); i != size; ++i) {
                ++count[src[i] - min];
        }
        // count[i] 保留着大於或等於i的元素的個數
        for (std::size_t i = 1; i != len; ++i) {
                count[i] += count[i - 1];
        }

        for (int i = src.size() - 1; i >= 0; --i) {
                dest[count[src[i] - min] - 1] = src[i];
                --count[src[i] - min];
        }
}
