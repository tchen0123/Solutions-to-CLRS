#include "inversion.h"

static std::size_t inversionNum = 0;

static void merge(std::vector<int> &array, std::size_t low, std::size_t high, std::size_t mid)
{
        std::size_t lSize = mid - low + 1, rSize = high - mid;
        int lArray[lSize], rArray[rSize];
        for (std::size_t i = 0; i != lSize; ++i) {
                lArray[i] = array[low + i];
        }
        for (std::size_t j = 0; j != rSize; ++j) {
                rArray[j] = array[mid + 1 + j];
        }

        for (std::size_t i = 0, j = 0, k = low;
             k <= high; ++k) {
                if (j >= rSize || (i < lSize && lArray[i] <= rArray[j])) {
                        array[k] = lArray[i++];
                }
                else {
                        array[k] = rArray[j++];
                        inversionNum += lSize - i;
                }
        }
}

int inversion(std::vector<int> &array, std::size_t low, std::size_t high)
{
        if (low < high) {
                std::size_t mid = (low + high) / 2;
                inversion(array, low, mid);
                inversion(array, mid + 1, high);
                merge(array, low, high, mid);
        }
        return inversionNum;
}
