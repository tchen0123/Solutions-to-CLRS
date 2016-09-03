#include "Kway_merge.h"
#include "minheap.h"
#include "list.h"
#include <iostream>
#include <cstdlib>

static void merge(std::size_t k, std::size_t n, struct List *listArray[],
                  struct Minheap &heap, std::vector<int> &result)
{
        while (!heapIsEmpty(heap)) {
                result.push_back(heap.array[0].value);

                std::size_t index = heap.array[0].index;
                struct List *tempNode = listArray[index];
                listArray[index] = listArray[index]->next;
                std::free(tempNode);

                if (listArray[index]) {
                        heap.array[0].value = listArray[index]->value;
                        heap.array[0].index = index;
                        minHeapify(heap, 0);
                }
                else {
                        //std::swap(heap.array[0], heap.array[heap.size - 1]);
                        heap.array[0]= heap.array[heap.size - 1];
                        --(heap.size);
                        minHeapify(heap, 0);
                }
        }
}

void KwayMerge(std::size_t k, std::size_t n)
{
        // 創建排好序的鏈表，幷儲存在數組中
        struct List *listArray[k];
        for (std::size_t i = 0; i != k; ++i) {
                listArray[i] = createList(n);
        }
        for (auto &i : listArray) {
                struct List *head = i;
                while (head) {
                        std::cout << head->value << " ";
                        head = head->next;
                }
                std::cout << std::endl;
        }

        // 先把鏈表首元素存在堆中
        struct Minheap heap;
        heap.size = k;
        for (std::size_t i = 0; i != k; ++i) {
                struct Node temp;
                temp.value = listArray[i]->value;
                temp.index = i;
                heap.array.push_back(temp);

                struct List *tempNode = listArray[i];
                listArray[i] = listArray[i]->next;
                std::free(tempNode);
        }
        buildMinheap(heap);

        // 開始歸幷
        std::vector<int> result;
        merge(k, n, listArray, heap, result);

        for (auto i : result) {
                std::cout << i << " ";
        }
        std::cout << std::endl;
}
