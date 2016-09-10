#ifndef CUT_ROD_H
#define CUT_ROD_H

#include <vector>


int cutRod(std::vector<int> &price, std::size_t length);
int memoizedCutRod(std::vector<int> &price, std::size_t length);
int bottomUpcutRod(std::vector<int> &price, std::size_t length, std::vector<int> &solution);

#endif
