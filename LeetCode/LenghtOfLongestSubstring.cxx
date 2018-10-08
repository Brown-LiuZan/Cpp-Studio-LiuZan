/****
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
****/

class Solution
{
public:
    int lengthOfLongestSubstring(string inStr)
    {
        if (inStr.size() == 0) return 0;
        
        unordered_map<char, size_t> vChar2IndexMap{{inStr[0], 0}};
        size_t vSubstrStartIndex = 0;
        size_t vSubstrEndIndex = 1;
        size_t vMaxLength = 1;
        size_t vNewSubstrStartIndex = 0;
        size_t vIndex = 1;
        while (vIndex < inStr.size())
        {
            auto vIt = vChar2IndexMap.find(inStr[vIndex]);
            if (vIt != vChar2IndexMap.end())
            {
                if (vIt->second >= vNewSubstrStartIndex)
                {
                    size_t vLength = vIndex - vNewSubstrStartIndex;
                    if (vLength > vMaxLength)
                    {
                        vSubstrStartIndex = vNewSubstrStartIndex;
                        vSubstrEndIndex = vIndex;
                        vMaxLength = vLength;
                    }
                    vNewSubstrStartIndex = vIt->second + 1;
                }
                vIt->second = vIndex;
            }
            else
            {
                vChar2IndexMap.emplace(inStr[vIndex], vIndex);
            }
            ++vIndex;
        }
        
        if (vIndex - vNewSubstrStartIndex > vMaxLength)
        {
            vSubstrStartIndex = vNewSubstrStartIndex;
            vSubstrEndIndex = vIndex;
        }
        
        return vSubstrEndIndex - vSubstrStartIndex;
    }
};
