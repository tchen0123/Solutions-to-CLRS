#include "binary_sum.h"

void binarySum(std::vector<unsigned> &A, std::vector<unsigned> &B, std::vector<unsigned> &C)
{
        unsigned over = 0;
        auto size = A.size();
        for (int i = size - 1; i >= 0; --i) {
                unsigned temp = A[i] + B[i] + over;
                if (temp > 1) {
                        C[i + 1] = temp % 2;
                        over = 1;
                }
                else {
                        C[i + 1] = temp;
                        over = 0;
                }
        }
        C[0] = over;
}
