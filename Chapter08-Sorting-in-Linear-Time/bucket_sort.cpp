#include "bucket_sort.h"

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

static void bubbleSort(std::vector<int> &array)
{
        std::size_t size = array.size();
        for (std::size_t i = 0; i != size - 1; ++i) {
                for (std::size_t j = size - 1; j != i; --j) {
                        if (array[j] < array[j - 1]) {
                                std::swap(array[j], array[j - 1]);
                        }
                }
        }
}


void bucketSort(std::vector<int> &array)
{
        // 求出最大最小值，通過相對量把數據映射到桶中
        int min = minimum(array), max = maximum(array);
        std::size_t len = max - min + 1;
        std::size_t size = array.size();

        //映射到桶中
        std::vector<std::vector<int>> bucket(size);
        for (std::size_t i = 0; i != size; ++i) {
                std::size_t index = (array[i] - min) / len * size;
                bucket[index].push_back(array[i]);
        }

        // 排序
        for (std::size_t i = 0; i != size; ++i) {
                if (bucket[i].size()) {
                        bubbleSort(bucket[i]);
                }
        }

        // 連接
        std::size_t cnt = 0;
        for (std::size_t i = 0; i != size; ++i) {
                std::size_t tempSize = bucket[i].size();
                if (tempSize) {
                        for (std::size_t j = 0; j != tempSize; ++j) {
                                array[cnt++] = bucket[i][j];
                        }
                }
        }
}
