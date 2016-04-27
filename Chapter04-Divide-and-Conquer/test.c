/*
 * Solutions-to-CLRS/Chapter04-Divide-and-Conquer/test.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "max_subarray.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
        int i;
        int array[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
        int maxLow, maxHigh, maxSum;

        printf("The input array is\n");
        for (i = 0; i < 16; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");

        MaxSubarray(array, 16, &maxLow, &maxHigh, &maxSum);

        printf("The maximum subarray is\n");
        for (i = maxLow; i <= maxHigh; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");

        return 0;
}
