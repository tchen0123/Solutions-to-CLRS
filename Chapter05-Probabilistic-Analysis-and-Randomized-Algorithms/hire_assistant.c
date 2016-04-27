/*
 * Chapter05-Probabilistic-Analysis-and-Randomized-Algorithms/hire_assistant.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "hire_assistant.h"
#include <stdlib.h>
#include <stdio.h>

static inline void Swap(int *a, int *b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}

/*
 * Randomized hire assistant.
 */
void HireAssistant(int array[], int size)
{
        int i;
        for (i = 1; i < size; i++) {
                int tempIndex = rand() % i;
                Swap(&array[i], &array[tempIndex]);
        }

        /*
        int i, priority[size];

        // Randomize priority array
        for (i = 0; i < size; i++) {
                priority[i] = rand() % (size * size * size);
        }

        // Insertion sort to priority array
        for (i = 1; i < size; i++) {
                int j, priKey, arrKey;

                j = i - 1;
                priKey = priority[i];
                arrKey = array[i];
                while (j >= 0 && priority[j] > priKey) {
                        priority[j + 1] = priority[j];
                        array[j + 1] = array[j];
                        j--;
                }
                priority[j + 1] = priKey;
                array[j + 1] = arrKey;
        }
        */
}
