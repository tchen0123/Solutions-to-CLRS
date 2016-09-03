#include "max_subarray.h"

Max findMaxCrossingSubarray(std::vector<int> &array, int low, int mid, int high)
{
        int left = mid;
        int leftSum = array[left];
        for (int i = mid , sum = 0; i >= low; --i) {
                sum += array[i];
                if (sum > leftSum) {
                        leftSum = sum;
                        left = i;
                }
        }

        int right = mid + 1;
        int rightSum = array[mid + 1];
        for (int i = mid + 1, sum = 0; i <= high; ++i) {
                sum += array[i];
                if (sum > rightSum) {
                        rightSum = sum;
                        right = i;
                }
        }

        Max ret(left, right, leftSum + rightSum);
        return ret;
}


// 遞歸算法
Max findMaxSubarray(std::vector<int> &array, int low, int high)
{
        if (low == high) {
                Max ret;
                ret.low = low;
                ret.high = high;
                ret.sum = array[low];

                return ret;
        }

        int mid = (low + high) / 2;

        Max leftMax = findMaxSubarray(array, low, mid);
        Max rightMax = findMaxSubarray(array, mid + 1, high);
        Max midMax = findMaxCrossingSubarray(array, low, mid, high);

        if (leftMax.sum >= rightMax.sum && leftMax.sum >= midMax.sum) {
                return leftMax;
        }
        else if (rightMax.sum >= leftMax.sum && rightMax.sum >= midMax.sum) {
                return rightMax;
        }
        else {
                return midMax;
        }
}


Max maxSubarray(std::vector<int> &array)
{
        Max ret(0, 0, 0);
        int tempSum = array[0], tempIndex = 0;

        for (std::size_t i = 1; i != array.size(); ++i) {
                if (tempSum < 0) {
                        tempSum = array[i];
                        tempIndex = i;
                }
                else {
                        tempSum += array[i];
                }

                if (tempSum > ret.sum) {
                        ret.sum = tempSum;
                        ret.low = tempIndex;
                        ret.high = i;
                }
        }

        return ret;
}
