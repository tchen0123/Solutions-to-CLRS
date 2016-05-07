/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/test.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "ostree.h"
#include "invl_tree.h"
#include <stdlib.h>
#include <limits.h>
#include <iostream>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

static void RandomizeArray(int array[], unsigned int size);
static void CreateInterval(struct invl_s array[], unsigned int size);

int main()
{
        unsigned int select;
        std::cout << "Please enter your choice:\n";
        std::cout << "1.Inversion test\n";
        std::cout << "2.Interval tree test\n";
        std::cin >> select;

        unsigned int size, i;

        std::cout << "Please enter the array size:\n";
        std::cin >> size;

        int array[size];
        struct invl_s intervals[size], tempInvl;
        unsigned int inversionSum = 0;

        struct ostree_s *ostree = InitOstreeNil();
        struct invlTree_s *invlTree = InitInvltreeNil();

        switch (select) {
        case 1:
                for (i = 0; i < size; i++) {
                        array[i] = i + 1;
                }
                RandomizeArray(array, size);

                std::cout << "The input array:\n";
                for (i = 0; i < size; i++) {
                        std::cout << array[i] << ' ';
                }
                std::cout << std::endl;

                for (i = 0; i < size; i++) {
                        ostree = OstreeInsert(ostree, array[i]);

                        // i + 1 is the current tree node number.
                        // OstreeRank is the number of tree nodes that are less than them.
                        inversionSum += i + 1 - OstreeRank(ostree, OstreeSearch(ostree, array[i]));
                }
                std::cout << "The number of inversions:\n";
                std::cout << inversionSum << std::endl;

                break;
        case 2:
                for (i = 0; i < size; i++) {
                        CreateInterval(intervals, size);
                }

                for (i = 0; i < size; i++) {
                        invlTree = InvltreeInsert(invlTree, intervals[i]);
                        std::cout << intervals[i].low << ", " << intervals[i].high << std::endl;
                }

                std::cout << "Tree walk by level\n";
                InvltreeWalkBylevel(invlTree);
                std::cout << std::endl;
                InvltreeWalkInorder(invlTree);
                std::cout << std::endl;

                std::cout << "Please enter a interval\n";
                std::cout << "Low:";
                std::cin >> tempInvl.low;
                std::cout << "High:";
                std::cin >> tempInvl.high;

                struct invlTree_s *tempPtr = InvltreeSearch(invlTree, tempInvl);
                if (tempPtr->maxEndpoint != INT_MIN) { // the treenil_g max endpoint is INT_MIN
                        std::cout << "The overlapping interval is ";
                        std::cout << '[' << tempPtr->interval.low << ", " << tempPtr->interval.high << ']';
                        std::cout << std::endl;
                } else {
                        std::cout << "No overlapping interval" << std::endl;
                }
                break;
        }

        DeleteOstree(ostree);
        DeleteInvltree(invlTree);

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

/*
 * Create intervals.
 */
static void CreateInterval(struct invl_s array[], unsigned int size)
{
        unsigned int i;
        for (i = 0; i < size; i++) {
                array[i].low = rand() % size;
                array[i].high = array[i].low + rand() % size;
        }
}
