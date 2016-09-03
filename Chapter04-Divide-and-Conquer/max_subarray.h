#ifndef MAX_SUBARRAY_H
#define MAX_SUBARRAY_H

#include <vector>


class Max {
public:
        Max(int l, int h, int s) : low(l), high(h), sum(s) { }
        Max() = default;
        int low, high;
        int sum;
};

Max findMaxSubarray(std::vector<int> &array, int low, int high);
Max maxSubarray(std::vector<int> &array);


#endif
