/*
 * Solutions-to-CLRS/Chapter02-Getting-Started/binary_sum.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * Binary numbers sum.
 */
void BinarySum(const int A[], const int B[], const int size, int sum[])
{
        int i, over, tempSum;

        over = 0;
        for (i = size - 1; i >= 0; i--) {
                tempSum = A[i] + B[i] + over;

                if (tempSum > 1) {
                        sum[i + 1] = tempSum % 2;
                        over = 1;
                } else {
                        sum[i + 1] = tempSum;
                        over = 0;
                }
        }
        sum[0] = over;
}
