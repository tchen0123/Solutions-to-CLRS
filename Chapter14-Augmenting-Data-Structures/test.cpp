/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/test.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "ostree.h"
#include <iostream>
#include <stdlib.h>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static void RandomizeArray(int array[], unsigned int size);

int main()
{
        unsigned int select = 0;
        std::cout << "Please enter your choice:\n";
        std::cout << "1.Order statistic test\n";
        std::cout << "2.Inversion test\n";
        std::cin >> select;

        unsigned int size = 0;
        std::cout << "Please enter the array size:\n";
        std::cin >> size;

        int array[size];
        unsigned int i = 0;
        for (i = 0; i < size; i++) {
                array[i] = i + 1;
        }
        RandomizeArray(array, size);

        struct ostree_s *ostree = InitOstreeNil();
        unsigned int inversionSum = 0;

        std::cout << "The input array:\n";
        for (i = 0; i < size; i++) {
                std::cout << array[i] << ' ';
        }
        std::cout << std::endl;

        switch (select) {
        case 1:
                for (i = 0; i < size; i++) {
                        ostree = OstreeInsert(ostree, array[i]);
                }
                std::cout << std::endl;

                std::cout << "Tree walk by level:\n";
                OstreeWalkBylevel(ostree);
                std::cout << std::endl;
                break;
        case 2:
                for (i = 0; i < size; i++) {
                        ostree = OstreeInsert(ostree, array[i]);

                        // i + 1 is the current tree node number.
                        // OstreeRank is the number of tree nodes that are less than them.
                        inversionSum += i + 1 - OstreeRank(ostree, OstreeSearch(ostree, array[i]));
                }
                std::cout << "The number of inversions:\n";
                std::cout << inversionSum << std::endl;
                break;
        }

        return 0;
}

/*
 * Randomize the array.
 */
static void RandomizeArray(int array[], unsigned int size)
{
        unsigned int i;
        for (i = 1; i < size; i++) {
                unsigned int tempIndex = rand() % i;
                Swap(&array[i], &array[tempIndex]);
        }
}
