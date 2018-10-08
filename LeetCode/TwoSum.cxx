/****
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
****/

class Solution {
public:  
    vector<int> twoSum(vector<int>& inrNums, int inTarget)
    {        
        unordered_multimap<int, int> vVal2IndexMap;
        for (int i = 1; i < inrNums.size(); ++i) vVal2IndexMap.emplace(inrNums[i], i);

        for (int i = 0; i < inrNums.size(); ++i)
        {
            auto vRange = vVal2IndexMap.equal_range(inTarget - inrNums[i]);
            for (auto vIt = vRange.first; vIt != vRange.second; ++vIt)
            {
                if (vIt->second != i) return vector<int>{i, vIt->second};                
            }
        }
        
        return vector<int>{};
    }
};
