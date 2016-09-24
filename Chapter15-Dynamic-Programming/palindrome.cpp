/*
 * 最長迴文子序列
 */
#include "palindrome.h"


int longestPalindrome(std::string &str, std::vector<std::vector<int>> &result)
{
        result.resize(str.size() + 1);
        for (auto &i : result) {
                i.resize(str.size() + 1, 0);
        }

        for (std::size_t low = str.size(); low != 0; --low) {
                for (std::size_t high = 1; high <= str.size(); ++high) {
                        if (low == high) {
                                result[low][high] = 1;
                        }
                        else if (low > high) {
                                result[low][high] = 0;
                        }
                        else if (str[low - 1] == str[high - 1]) {
                                result[low][high] = result[low + 1][high - 1] + 2;
                        }
                        else {
                                result[low][high] = std::max(result[low + 1][high], result[low][high - 1]);
                        }
                }
        }
        return result[1][str.size()];
}
