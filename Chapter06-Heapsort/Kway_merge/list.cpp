#include "list.h"
#include <cstdlib>
#include <vector>

static inline struct List *createNode(int value)
{
        struct List *newNode = (struct List *)std::malloc(sizeof(struct List));
        newNode->value = value;
        newNode->next = nullptr;

        return newNode;
}

static void insertionSort(std::vector<int> &array)
{
        for (std::size_t i = 1, size = array.size();
             i != size; ++i) {
                int key = array[i], j = i - 1;
                while (j >= 0 && array[j] > key) {
                        array[j + 1] = array[j];
                        --j;
                }
                array[j + 1] = key;
        }
}

struct List *createList(std::size_t n)
{
        // 創建一個隨機數組，排序，再存在鏈表中
        std::vector<int> array(n);
        for (auto &i : array) {
                i = std::rand() % n;
        }
        insertionSort(array);

        struct List *head = nullptr, *tempPtr;
        for (std::size_t i = 0 ; i != n; ++i) {

                if (!head) {
                        head = createNode(array[i]);
                        tempPtr = head;
                }
                else {
                        tempPtr->next = createNode(array[i]);
                        tempPtr = tempPtr->next;
                }
        }

        return head;
}
