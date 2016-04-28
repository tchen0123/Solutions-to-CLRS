/*
 * Solutions-to-CLRS/Chapter06-Heapsort/heap.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __HEAP_H_
#define __HEAP_H_

#define PARENT(i)  (i - 1) / 2
#define LEFT(i)    i * 2 + 1
#define RIGHT(i)   i * 2 + 2

void MaxHeapify(int array[], int size, int i);
void MinHeapify(int array[], int size, int i);
void BuildMaxHeap(int array[], int size);
void BuildMinHeap(int array[], int size);

#endif
