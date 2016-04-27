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

        printf("The input array is\n");
        for (i = 0; i < 16; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");

        struct maxSubarray_s subarray;

        //subarray = MaxSubarray(array, 16);
        subarray = FindMaxSubarray(array, 0, 15);

        printf("The maximum subarray is\n");
        for (i = subarray.low; i <= subarray.high; i++) {
                printf("%d ", array[i]);
        }
        printf("\n\n");
        printf("Sum of the maximum subarray is %d\n", subarray.sum);

        return 0;
}
