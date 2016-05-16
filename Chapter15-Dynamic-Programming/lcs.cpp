/*
 * Solutions-to-CLRS/Chapter15-Dynamic-Programming/lcs.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * LCS: Longest common subsequence
 * LIS: Longest monotonically increasing subsequence
 */

#include <iostream>
#include <string>
#include <vector>

#define MAX_LENGTH  100 // max sequence length


// Partition for quick sort
static inline size_t Partition(std::vector<int> &array, size_t begin, size_t end)
{
        int pivot = array[end];

        int less = begin - 1; // begin may be zero
        for (size_t larger = begin; larger != end; ++larger) {
                if (array[larger] <= pivot) {
                        less++;
                        int temp = array[larger];
                        array[larger] = array[less];
                        array[less] = temp;
                }
        }

        int temp = array[end];
        array[end] = array[less + 1];
        array[less + 1] = temp;

        return less + 1;
}


size_t LCSLength(const std::string &xStr, const std::string &yStr,
                 unsigned (&path)[MAX_LENGTH][MAX_LENGTH]);

void PrintLCS(const std::string &yStr, const unsigned(&path)[MAX_LENGTH][MAX_LENGTH],
              size_t xLength, size_t yLength);

void QuickSort(std::vector<int> &array, int begin, int end);

size_t LISLength(const std::vector<int> &array, unsigned (&length)[MAX_LENGTH + 1][MAX_LENGTH + 1]);

void PrintLIS(const std::vector<int> &array, unsigned (&length)[MAX_LENGTH + 1][MAX_LENGTH + 1],
              size_t length1, size_t length2);


int main()
{
        std::cout << "Please enter your chioce:\n";
        std::cout << "1.Longest-common-subsequence problem\n";
        std::cout << "2.Monotonically-increasing-subsequence problem\n";
        unsigned select;
        std::cin >> select;

        switch (select) {
        case 1: {
                std::cout << "Please enter two sequences:\n";
                std::string xStr, yStr;
                std::cin >> xStr >> yStr;

                if (xStr.size() > MAX_LENGTH || yStr.size() > MAX_LENGTH) {
                        std::cout << "The length of sequence should be less than " << MAX_LENGTH << std::endl;
                        return 0;
                }

                unsigned path[MAX_LENGTH][MAX_LENGTH];
                std::cout << "The LCS length: " << LCSLength(xStr, yStr, path) << std::endl;;
                std::cout << "The LCS: ";
                PrintLCS(yStr, path, xStr.size(), yStr.size());
                std::cout << std::endl;
        }
                break;
        case 2: {
                std::cout << "Please enter an integer number sequence:\n";
                std::vector<int> array;

                int temp;
                while (std::cin >> temp) {
                        array.push_back(temp);
                }

                unsigned length[MAX_LENGTH + 1][MAX_LENGTH + 1];

                std::cout << "The LIS length: " << LISLength(array, length) << std::endl;
                std::cout << "The LIS: ";
                PrintLIS(array, length, array.size(), array.size());
                std::cout << std::endl;
        }
                break;
        default:
                break;
        }

        return 0;
}

/*
 * Calculate the length of LCS.
 */
size_t LCSLength(const std::string &xStr, const std::string &yStr,
                 unsigned (&path)[MAX_LENGTH][MAX_LENGTH])
{
        size_t xLength = xStr.size(), yLength = yStr.size();
        size_t length[xLength + 1][yLength + 1];

        // Initialize
        for (auto &i : length) {
                for (auto &j : i) {
                        j = 0;
                }
        }

        for (size_t i = 1; i != xLength + 1; ++i) {
                for (size_t j = 1; j != yLength + 1; ++j) {
                        if (xStr[i] == yStr[j]) {
                                length[i][j] = length[i - 1][j - 1] + 1;
                                path[i - 1][j - 1] = 0;
                        } else if (length[i - 1][j] >= length[i][j - 1]) {
                                length[i][j] = length[i - 1][j];
                                path[i - 1][j - 1] = 1;
                        } else {
                                length[i][j] = length[i][j - 1];
                                path[i - 1][j - 1] = 2;
                        }
                }
        }

        return length[xLength][yLength];
}

/*
 * Print the LCS.
 */
void PrintLCS(const std::string &yStr, const unsigned(&path)[MAX_LENGTH][MAX_LENGTH],
              size_t xLength, size_t yLength)
{
        if (xLength == 0 || yLength == 0) {
                return;
        }

        if (path[xLength][yLength] == 0) {
                PrintLCS(yStr, path, xLength - 1, yLength - 1);
                std::cout << yStr[yLength - 1];
        } else if (path[xLength][yLength] == 1) {
                PrintLCS(yStr, path, xLength - 1, yLength);
        } else {
                PrintLCS(yStr, path, xLength, yLength - 1);
        }
}

/*
 * Calculate the length of LIS.
 *
 * First sort X and create another sequence X'.
 * Finding the longest common subsequence fo X and X' yields the monotonically
 * increasing subsequence of X.
 */
size_t LISLength(const std::vector<int> &array, unsigned (&length)[MAX_LENGTH + 1][MAX_LENGTH + 1])
{
        // Create another array and sort
        std::vector<int> tempArray = array;
        size_t size = tempArray.size();

        // Quick sort
        QuickSort(tempArray, 0, size - 1);

        // Initialize
        for (unsigned i = 0; i != size + 1; ++i) {
                for (unsigned j = 0; j != size + 1; ++j) {
                        length[i][j] = 0;
                }
        }

        for (unsigned i = 1; i != size + 1; ++i) {
                for (unsigned j = 1; j != size + 1; ++j) {
                        if (array[i - 1] == tempArray[j - 1]) {
                                length[i][j] = length[i - 1][j - 1] + 1;
                        } else if (length[i - 1][j] >= length[i][j - 1]) {
                                length[i][j] = length[i - 1][j];
                        } else {
                                length[i][j] = length[i][j - 1];
                        }
                }
        }

        return length[size][size];
}

/*
 * Quick sort.
 */
void QuickSort(std::vector<int> &array, int begin, int end)
{
        if (begin < end) {
                int index = Partition(array, begin, end);
                QuickSort(array, begin, index - 1);
                QuickSort(array, index + 1, end);
        }
}

/*
 * Print the LIS.
 */
void PrintLIS(const std::vector<int> &array, unsigned (&length)[MAX_LENGTH + 1][MAX_LENGTH + 1],
              size_t length1, size_t length2)
{
        if (length1 == 0 || length2 == 0) {
                return;
        }

        if (length[length1][length2] == length[length1 - 1][length2 - 1] + 1) {
                PrintLIS(array, length, length1 - 1, length2 - 1);
                std::cout << array[length1 - 1] << ' ';
        } else if (length[length1][length2] == length[length1 - 1][length2]) {
                PrintLIS(array, length, length1 - 1, length2);
        } else {
                PrintLIS(array, length, length1, length2 - 1);
        }
}
