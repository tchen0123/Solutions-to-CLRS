/*
 * Solutions-to-CLRS/Chapter15-Dynamic-Programming/lcs.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

/*
 * Longest-common-subsequence problem
 */

#include <iostream>
#include <string>
#include <vector>


#define MAX_LENGTH   100


size_t LCSLength(const std::string &xStr, const std::string &yStr, unsigned(&path)[MAX_LENGTH][MAX_LENGTH]);
void PrintLCS(const unsigned(&path)[MAX_LENGTH][MAX_LENGTH], const std::string &yStr,
              const size_t xLength, const size_t yLength);


int main()
{
        std::cout << "Please enter two strings:\n";

        std::string xStr, yStr;
        std::cin >> xStr >> yStr;

        if (xStr.size() > MAX_LENGTH || yStr.size() > MAX_LENGTH) {
                std::cout << "string's size should be less than 100." << std::endl;
        }

        unsigned path[MAX_LENGTH][MAX_LENGTH];
        std::cout << "LCS length: " << LCSLength(xStr, yStr, path) << std::endl;
        std::cout << "LCS: ";
        PrintLCS(path, yStr, xStr.size(), yStr.size());
        std::cout << std::endl;

        return 0;
}

/*
 * Calculate the length of LCS.
 */
size_t LCSLength(const std::string &xStr, const std::string &yStr, unsigned(&path)[MAX_LENGTH][MAX_LENGTH])
{
        size_t xLength = xStr.size(), yLength = yStr.size();
        size_t length[xLength + 1][yLength + 1];

        // Initialize length array
        for (size_t i = 0; i != xLength + 1; ++i) {
                for (size_t j = 0; j != yLength + 1; ++j) {
                        length[i][j] = 0;
                }
        }

        for (size_t i = 1; i != yLength + 1; ++i) {
                for (size_t j = 1; j != yLength + 1; ++j) {
                        if (xStr[i - 1] == yStr[j - 1]) {
                                length[i][j] = length[i - 1][j - 1] + 1;
                                path[i - 1][j - 1] = 0;
                        } else {
                                if (length[i - 1][j] >= length[i][j - 1]) {
                                        length[i][j] = length[i - 1][j];
                                        path[i - 1][j - 1] = 1;
                                } else {
                                        length[i][j] = length[i][j - 1];
                                        path[i - 1][j - 1] = 2;
                                }
                        }
                }
        }

        return length[xLength][yLength];
}

/*
 * Print the LCS.
 */
void PrintLCS(const unsigned(&path)[MAX_LENGTH][MAX_LENGTH], const std::string &yStr,
              const size_t xLength, const size_t yLength)
{
        if (xLength == 0 || yLength == 0) {
                return;
        }

        if (path[xLength - 1][yLength - 1] == 0) {
                PrintLCS(path, yStr, xLength - 1, yLength - 1);
                std::cout << yStr[yLength - 1];
        } else if (path[xLength - 1][yLength - 1] == 1) {
                PrintLCS(path, yStr, xLength - 1, yLength);
        } else {
                PrintLCS(path, yStr, xLength, yLength - 1);
        }
}
