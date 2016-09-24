#ifndef LCS_H
#define LCS_H

#include <vector>
#include <string>

int LCS_Length(std::string &A, std::string &B, std::vector<std::vector<int>> &result);
void printLCS(std::string &A, std::size_t ALen, std::size_t BLen, std::vector<std::vector<int>> &result);

#endif
