#if __std_cplusplus >= CPLUSPLUS_VAL_FOR_11

#define DYNAMIC_ASSERT_ERRMSG

#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

#include "Common/cxx_version_macroes.h"
#include "Common/assert.h"


namespace epi {
    using PositiveInteger = unsigned;

    PositiveInteger FindSmallestNonExistSum(
            std::vector<PositiveInteger> const & numbers)
    {
        DynamicAssert(numbers.size() > 0);

        std::vector<PositiveInteger> ascendNumbers(numbers);

        std::sort(ascendNumbers.begin(), ascendNumbers.end());
        auto it = ascendNumbers.begin();
        DynamicAssert(*it > 0);
        bool isCombinable = (1 == *it);
        PositiveInteger result = *it + 1;
        while (++it != ascendNumbers.end()) {
            if (isCombinable) {
                if (*it > result) return result;
                result += *it;
            } else {
                if (*it != result) return result;
                else ++result;
            }
        }
        return result;
    }

    PositiveInteger FindSmallestNonExistSum(
            std::vector<PositiveInteger> * numbers)
    {
        DynamicAssert(numbers->size() > 0);

        std::sort(numbers->begin(), numbers->end());
        auto it = numbers->begin();
        DynamicAssert(*it > 0);
        bool isCombinable = (1 == *it);
        PositiveInteger result = *it + 1;
        while (++it != numbers->end()) {
            if (isCombinable) {
                if (*it > result) return result;
                result += *it;
            } else {
                if (*it != result) return result;
                else ++result;
            }
        }
        return result;
    }
}

using namespace testing;
TEST(EPI, TestFindSmallestNonExistSum)
{
    std::vector<epi::PositiveInteger> piSet1{5, 4, 2, 3, 9};
    epi::PositiveInteger result1{6};
    EXPECT_EQ(result1, epi::FindSmallestNonExistSum(piSet1))
        << "The smallest non-exist sum of {5, 4, 2, 3, 9} should be 6.";
    EXPECT_EQ(result1, epi::FindSmallestNonExistSum(&piSet1))
        << "The smallest non-exist sum of {5, 4, 2, 3, 9} should be 6.";
}

#endif
