#ifndef CUT_ROD_H
#define CUT_ROD_H

#include <vector>

int cutRod(std::vector<int> &price, std::size_t len);
int memoizedCutRod(std::vector<int> &price, std::size_t len);
int bottomUpCutRod(std::vector<int> &price, std::size_t len, std::vector<int> &solution);

#endif
