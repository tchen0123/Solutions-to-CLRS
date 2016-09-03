#include "randomize.h"
#include <cstdlib>

static void bubbleSort(std::vector<int> &array, std::vector<int> &P)
{
        for (int i = 0, size = array.size(); i != size; ++i) {
                for (int j = size - 1; j != i; --j) {
                        if (P[j] < P[j - 1]) {
                                std::swap(P[j], P[j - 1]);
                                std::swap(array[j], array[j - 1]);
                        }
                }
        }
}

void permuteBySorting(std::vector<int> &array)
{
        std::vector<int> P;
        for(std::size_t i = 0, size = array.size(); i != size; ++i) {
                P.push_back(std::rand() % (size * size * size));
        }

        bubbleSort(array, P);
}

void randomizeInPlace(std::vector<int> &array)
{
        for (std::size_t i = 1, size = array.size(); i != size; ++i) {
                std::size_t temp = std::rand() % i;
                std::swap(array[i], array[temp]);
        }
}
