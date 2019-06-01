#include "Common/cxx_version_macroes.h"

// Mathematical functions and types
#if __cplusplus > CPLUSPLUS_VAL_FOR_98
#include <cinttypes>
#else
#include <stdint.h>
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
#include <cstdlib>
#include <cmath>
#include <limits>
#include <complex>
#if __cplusplus > CPLUSPLUS_VAL_FOR_98
#include <valarray>
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
// Numeric algorithms
#include <cmath> //Deliberately redundant
#include <numeric>
// Miscellanous
#include <random>
#if __cplusplus > CPLUSPLUS_VAL_FOR_98
#include <ratio>
#include <cfenv>
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
#if __cplusplus > CPLUSPLUS_VAL_FOR_17
#include <bit>
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_17

#include <gtest/gtest.h>

using namespace std;

TEST(MathFunc, IntegerFunc)
{
    {
        int expected = 9, argument = -9;    
        EXPECT_EQ(expected, abs(argument));
    }
    {
        long expected = 9, argument = -9;    
        EXPECT_EQ(expected, abs(argument));
    }
    {
        long long expected = 9, argument = -9;    
        EXPECT_EQ(expected, abs(argument));
    }
    #if __cplusplus > CPLUSPLUS_VAL_FOR_98
    {
        int x = -13, y = 3;
        div_t expected;
        expected.quot = x / y;
        expected.rem = x % y;
        div_t value = div(x, y);
        EXPECT_EQ(expected.quot, value.quot);
        EXPECT_EQ(expected.rem, value.rem);
    }
    {
        long x = -13, y = 3;
        ldiv_t expected;
        expected.quot = x / y;
        expected.rem = x % y;
        ldiv_t value = div(x, y);
        EXPECT_EQ(expected.quot, value.quot);
        EXPECT_EQ(expected.rem, value.rem);
    }
    {
        long long x = -13, y = 3;
        lldiv_t expected;
        expected.quot = x / y;
        expected.rem = x % y;
        lldiv_t value = div(x, y);
        EXPECT_EQ(expected.quot, value.quot);
        EXPECT_EQ(expected.rem, value.rem);
    }
    #endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
}
