/*
 * Solutions-to-CLRS/Chapter09-Medians-and-Order-Statistics/select.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "select.h"
#include <stdlib.h>

/*
 * Select the randomed number between head and tail.
 */
static inline int Random(int head, int tail)
{
        int len = tail - head + 1;

        return ((rand() % len) + tail);
}

static int RandomPartition(int array[], int head, int tail);
