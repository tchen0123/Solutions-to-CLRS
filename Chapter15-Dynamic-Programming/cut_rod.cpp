#include "cut_rod.h"
#include <iostream>

static int memoizedCutRodAux(std::vector<int> &price, std::size_t len,
                             std::vector<int> &memo)
{
        if (memo[len] > 0) {
                return memo[len];
        }
        if (len == 0) {
                memo[len] = 0;
                return 0;
        }

        int result = 0;
        for (std::size_t i = 1; i <= len; ++i) {
                result = std::max(result, price[i] + memoizedCutRodAux(price, len - i, memo));
        }
        memo[len] = result;
        return result;
}

int cutRod(std::vector<int> &price, std::size_t len)
{
        if (len == 0) {
                return 0;
        }

        int result = -1;
        for (std::size_t i = 1; i <= len; ++i) {
                result = std::max(result, price[i] + cutRod(price, len - i));
        }
        return result;
}

int memoizedCutRod(std::vector<int> &price, std::size_t len)
{
        std::vector<int> memo(len + 1, -1);
        return memoizedCutRodAux(price, len, memo);
}

int bottomUpCutRod(std::vector<int> &price, std::size_t len, std::vector<int> &solution)
{
        std::vector<int> memo(len + 1, 0);
        solution.resize(len + 1, 0);
        for (std::size_t i = 1; i <= len; ++i) {
                int max = 0;
                for (std::size_t j = 1; j <= i; ++j) {
                        int temp = price[j] + memo[i - j];
                        if (temp > max) {
                                max = temp;
                                solution[i] = j;
                        }
                }
                memo[i] = max;
        }
        return memo[len];
}

void printSolution(std::vector<int> &solution, int len)
{
        while (len){
                std::cout << solution[len] << " ";
                len -= solution[len];
        }
}
