/*
 * Longest palindrome
 */
#include "palindrome.h"
#include <vector>

int palindrome(std::string &str)
{
        std::vector<std::vector<int>> count;
        count.resize(str.size() + 1); // 這裏大小爲str.size() + 1的原因是，
                                      // 當low = str.size() - 1時，count[low + 1]即count[str.size()]。
        for (auto &i : count) {
                i.resize(str.size(), 0);
        }

        for (int low = str.size() - 1; low >= 0; --low) {
                for (int high = 0; high < static_cast<int>(str.size()); ++high) {
                        if (low == high) {
                                count[low][high] = 1;
                        }
                        else if (low > high) {
                                count[low][high] = 0;
                        }
                        else if (str[low] == str[high]) {
                                count[low][high] = count[low + 1][high - 1] + 2;
                        }
                        else {
                                count[low][high] = std::max(count[low + 1][high], count[low][high - 1]);
                        }
                }
        }
        return count[0][str.size() - 1];
}
