/*
 * Chapter05-Probabilistic-Analysis-and-Randomized-Algorithms/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "hire_assistant.h"
#include <stdio.h>

int main(void)
{
        int i, size;

        printf("How many integer numbers do you want to enter?\n");
        scanf("%d", &size);

        int array[size];
        printf("The input array:\n");
        for (i = 0; i < size; i++) {
                array[i] = i + 1;
                printf("%d ", array[i]);
        }
        printf("\n\n");

        HireAssistant(array, size);

        printf("The randomized array:\n");
        for (i = 0; i < size; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");

        return 0;
}
