#include "cut_rod.h"

int memoizedCutRodAux(std::vector<int> &price, std::size_t length,
                      std::vector<int> &memo)
{
        if (memo[length] >= 0) {
                return memo[length];
        }

        if (length == 0) {
                return 0;
        }

        int max = 0;
        for (std::size_t i = 0; i != length; ++i) {
                max = std::max(max, price[i] + memoizedCutRodAux(price, length - i - 1, memo));
        }
        memo[length] = max;
        return max;
}

int cutRod(std::vector<int> &price, std::size_t length)
{
        if (length == 0) {
                return 0;
        }

        int max = 0;
        for (std::size_t i = 0; i != length; ++i) {
                max = std::max(max, price[i] + cutRod(price, length - i - 1));
        }
        return max;
}

int memoizedCutRod(std::vector<int> &price, std::size_t length)
{
        std::vector<int> memo(length + 1, -1);
        return memoizedCutRodAux(price, length, memo);
}

int bottomUpcutRod(std::vector<int> &price, std::size_t length, std::vector<int> &solution)
{
        std::vector<int> memo(length + 1);
        memo[0] = 0;

        for (std::size_t i = 1; i <= length; ++i) {
                int max = 0;
                for (std::size_t j = 1; j <= i; ++j) {
                        if (max < price[j - 1] + memo[i - j]) {
                                max = price[j - 1] + memo[i - j];
                                solution[i] = j;
                        }
                }
                memo[i] = max;
        }
        return memo[length];
}
