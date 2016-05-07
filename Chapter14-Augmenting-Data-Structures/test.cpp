/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/test.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "ostree.h"
#include <stdlib.h>
#include <iostream>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static void RandomizeArray(int array[], unsigned int size);

int main()
{
        unsigned int select;
        std::cout << "Please enter your choice:\n";
        std::cout << "1.Inversion test\n";
        std::cin >> select;

        unsigned int size;
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

                        // i + 1 is the current tree node number.
                        // OstreeRank is the number of tree nodes that are less than them.
                        inversionSum += i + 1 - OstreeRank(ostree, OstreeSearch(ostree, array[i]));
                }
                std::cout << "The number of inversions:\n";
                std::cout << inversionSum << std::endl;

                DeleteOstree(ostree);
                break;
        }

        return 0;
}

/*
 * Randomize arrray.
 */
static void RandomizeArray(int array[], unsigned int size)
{
        unsigned int i;
        for (i = 1; i < size; i++) {
                unsigned int tempIndex = rand() % i;
                Swap(&array[i], &array[tempIndex]);
        }
}
