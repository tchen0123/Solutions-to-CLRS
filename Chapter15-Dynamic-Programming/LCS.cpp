#include "LCS.h"
#include <iostream>

int LCS_Length(std::string &A, std::string &B, std::vector<std::vector<int>> &result)
{
        result.resize(A.size() + 1);
        for (auto &i : result) {
                i.resize(B.size() + 1, 0);
        }

        for (std::size_t i = 1; i <= A.size(); ++i) {
                for (std::size_t j = 1; j <= B.size(); ++j) {
                        if (A[i - 1] == B[j - 1]) {
                                result[i][j] = result[i - 1][j - 1] + 1;
                        }
                        else if (result[i - 1][j] >= result[i][j - 1]) {
                                result[i][j] = result[i - 1][j];
                        }
                        else {
                                result[i][j] = result[i][j - 1];
                        }
                }
        }
        return result[A.size()][B.size()];
}

void printLCS(std::string &A, std::size_t ALen, std::size_t BLen, std::vector<std::vector<int>> &result)
{
        if (ALen == 0 || BLen == 0) {
                return;
        }
        if (result[ALen][BLen] == result[ALen - 1][BLen - 1] + 1) {
                printLCS(A, ALen - 1, BLen - 1, result);
                std::cout << A[ALen - 1];
        }
        else if (result[ALen][BLen] == result[ALen - 1][BLen]) {
                printLCS(A, ALen - 1, BLen, result);
        }
        else {
                printLCS(A, ALen, BLen - 1, result);
        }
}
