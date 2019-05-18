#include <iostream>
#include <vector>
#include <unordered_map>

#include <gtest/gtest.h>

#include "Common/cxx_version_macroes.h"

/****
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
****/

using namespace std;

class Solution {
public:  
    vector<int> twoSum(vector<int>& inrNums, int inTarget)
    {        
        unordered_multimap<int, int> vVal2IndexMap;
        for (int i = 1; i < static_cast<int>(inrNums.size()); ++i) {
            vVal2IndexMap.emplace(inrNums[i], i);
        }

        for (int i = 0; i < static_cast<int>(inrNums.size()); ++i) {
            auto vRange = vVal2IndexMap.equal_range(inTarget - inrNums[i]);
            for (auto vIt = vRange.first; vIt != vRange.second; ++vIt)
            {
                if (vIt->second != i) return vector<int>{i, vIt->second};                
            }
        }
        
        return vector<int>{};
    }
};

#if __std_cplusplus >= CPLUSPLUS_VAL_FOR_11
TEST_F(Solution, TestTwoSumSolution)
{
    vector<int> nums{2, 7, 11, 15};
    cout << "Given numbers: ";
    for (auto i : nums) {
        cout << i << ' ';
    }
    cout << endl;
    cout << "Target: 9" << endl;
    auto result = twoSum(nums, 9);
    cout << "Result: (" << result[0] << ',' << result[1] << ')' << endl;
    EXPECT_EQ(0, result[0]);
    EXPECT_EQ(1, result[1]);
}
#endif // __std_cplusplus
