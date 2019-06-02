/**
 * Key observations:
 *     - Unsigned integer minus one will flip all bits starting from the least
 *     significant bit already set.
 *     - XOR unsigned integers is associative and cummutative. It will produce
 *     parities of each bit in this kind of unsigned integer.
 */

#include "Common/cxx_version_macroes.h"

#if __cplusplus > CPLUSPLUS_VAL_FOR_98
#include <cinttypes>
#include <chrono>
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
#include <iostream>

#include <gtest/gtest.h>

using namespace std;

#if __cplusplus > CPLUSPLUS_VAL_FOR_98
constexpr uint64_t GetLowestSetBit(uint64_t inVal)
{
    if (0 == inVal) {
        return 0;
    }
    else {
        uint64_t vTemp = inVal - 1;
        return (inVal ^ vTemp) & inVal;
    }
}

constexpr uint64_t GetLowestUnsetBit(uint64_t inVal)
{
    uint64_t vComp = ~inVal;
    return GetLowestSetBit(vComp);
}

TEST(TSEpiIntOps, TCGetLowestSetBit)
{
    EXPECT_EQ(0ULL, GetLowestSetBit(0ULL));
    EXPECT_EQ(0x00010000, GetLowestSetBit(0x11010000));
    EXPECT_EQ(0ULL, GetLowestUnsetBit(static_cast<uint64_t>(-1)));
    EXPECT_EQ(0x00001000, GetLowestUnsetBit(0x000FEFFF));
}

constexpr bool IsPowerOfTwo(uint64_t inVal)
{
    if (0 == inVal) {
        return false;
    } else {
        return 0 == (inVal & (inVal - 1));
    }
}

TEST(TSEpiIntOps, TCIsPowerOfTwo)
{
    EXPECT_FALSE(IsPowerOfTwo(0));
    EXPECT_FALSE(IsPowerOfTwo(1023));
    EXPECT_TRUE(IsPowerOfTwo(1024));
}

constexpr bool HasOddOnes(uint64_t inVal)
{
    inVal ^= inVal >> 32;
    inVal ^= inVal >> 16;
    inVal ^= inVal >> 8;
    inVal ^= inVal >> 4;
    inVal ^= inVal >> 2;
    inVal ^= inVal >> 1;
    return 1U == (inVal & 1U);
}

constexpr bool HasOddOnes(uint32_t inVal)
{
    inVal ^= inVal >> 16;
    inVal ^= inVal >> 8;
    inVal ^= inVal >> 4;
    inVal ^= inVal >> 2;
    inVal ^= inVal >> 1;
    return 1U == (inVal & 1U);
}

constexpr bool HasOddOnes(uint16_t inVal)
{
    inVal ^= inVal >> 8;
    inVal ^= inVal >> 4;
    inVal ^= inVal >> 2;
    inVal ^= inVal >> 1;
    return 1U == (inVal & 1U);
}

constexpr bool HasOddOnes(uint8_t inVal)
{
    inVal ^= inVal >> 4;
    inVal ^= inVal >> 2;
    inVal ^= inVal >> 1;
    return 1U == (inVal & 1U);
}

class HasOddOnes
{
public:
    static constexpr bool Result(uint64_t inVal)
    {
        inVal ^= inVal >> 32;
        inVal ^= inVal >> 16;
        inVal ^= inVal >> 8;
        inVal ^= inVal >> 4;
        return mResultOf4bits[inVal & 0x0F];
    }
    static constexpr bool Result(uint32_t inVal)
    {
        inVal ^= inVal >> 16;
        inVal ^= inVal >> 8;
        inVal ^= inVal >> 4;
        return mResultOf4bits[inVal & 0x0F];
    }
    static constexpr bool Result(uint16_t inVal)
    {
        inVal ^= inVal >> 8;
        inVal ^= inVal >> 4;
        return mResultOf4bits[inVal & 0x0F];
    }
    static constexpr bool Result(uint8_t inVal)
    {
        inVal ^= inVal >> 4;
        return mResultOf4bits[inVal & 0x0F];
    }
private:
    //static constexpr bool mResultOf4bits[16];
    static constexpr bool mResultOf4bits[16] = {
        false, true, true, false,
        true, false, false, true,
        true, false, false, true,
        false, true, true, false
    };
};

TEST(TSEpiIntOps, TCHasOddOnes)
{
    EXPECT_FALSE(HasOddOnes(static_cast<uint64_t>(0xFFFFFFFFFFFFFFFFULL)));
    EXPECT_FALSE(HasOddOnes(static_cast<uint64_t>(0x0001020304050607ULL)));
    EXPECT_TRUE(HasOddOnes(static_cast<uint64_t>(0x0E01020304050607ULL)));
    EXPECT_FALSE(HasOddOnes(static_cast<uint64_t>(0)));
    EXPECT_TRUE(HasOddOnes(static_cast<uint64_t>(1)));
    EXPECT_FALSE(HasOddOnes(static_cast<uint64_t>(3)));
    EXPECT_TRUE(HasOddOnes(static_cast<uint64_t>(7)));
    EXPECT_FALSE(HasOddOnes(static_cast<uint32_t>(0)));
    EXPECT_TRUE(HasOddOnes(static_cast<uint32_t>(1)));
    EXPECT_FALSE(HasOddOnes(static_cast<uint32_t>(3)));
    EXPECT_TRUE(HasOddOnes(static_cast<uint32_t>(7)));
    EXPECT_FALSE(HasOddOnes(static_cast<uint16_t>(0)));
    EXPECT_TRUE(HasOddOnes(static_cast<uint16_t>(1)));
    EXPECT_FALSE(HasOddOnes(static_cast<uint16_t>(3)));
    EXPECT_TRUE(HasOddOnes(static_cast<uint16_t>(7)));
    EXPECT_FALSE(HasOddOnes(static_cast<uint8_t>(0)));
    EXPECT_TRUE(HasOddOnes(static_cast<uint8_t>(1)));
    EXPECT_FALSE(HasOddOnes(static_cast<uint8_t>(3)));
    EXPECT_TRUE(HasOddOnes(static_cast<uint8_t>(7)));
    EXPECT_FALSE(HasOddOnes::Result(static_cast<uint64_t>(0xFFFFFFFFFFFFFFFFULL)));
    EXPECT_FALSE(HasOddOnes::Result(static_cast<uint64_t>(0x0001020304050607ULL)));
    EXPECT_TRUE(HasOddOnes::Result(static_cast<uint64_t>(0x0E01020304050607ULL)));
    EXPECT_FALSE(HasOddOnes::Result(static_cast<uint64_t>(0)));
    EXPECT_TRUE(HasOddOnes::Result(static_cast<uint64_t>(1)));
    EXPECT_FALSE(HasOddOnes::Result(static_cast<uint64_t>(3)));
    EXPECT_TRUE(HasOddOnes::Result(static_cast<uint64_t>(7)));

    auto start = chrono::steady_clock::now();
    int vOdds = 0, vEvens = 0;
    for (uint64_t i = 0; i < 10000000; ++i) {
        if (HasOddOnes(i)) {
            ++vOdds;
        } else {
            ++vEvens;
        }
    }
    EXPECT_EQ(vOdds, vEvens);
    auto end = chrono::steady_clock::now();
    chrono::duration<double> vSecs = end - start;
    cout << "HasOddOnes(i)s consume " << vSecs.count() << "s" << endl;

    start = chrono::steady_clock::now();
    vOdds = 0, vEvens = 0;
    for (uint64_t i = 0; i < 10000000; ++i) {
        if (HasOddOnes::Result(i)) {
            ++vOdds;
        } else {
            ++vEvens;
        }
    }
    EXPECT_EQ(vOdds, vEvens);
    end = chrono::steady_clock::now();
    vSecs = end - start;
    cout << "HasOddOnes::Result(i)s consume " << vSecs.count() << "s" << endl;
}

constexpr int CountOnes(uint64_t inVal)
{
    int vCnt = 0;
    while (inVal > 0) {
        ++vCnt;
        inVal &= inVal - 1;
    }
    return vCnt;
}

int CountOnes(uint8_t inArr[], int inCount)
{
    uint8_t *vpByte = inArr;
    int vResidue = inCount;
    int vSum = 0;
    while ((reinterpret_cast<uint64_t>(vpByte) & 0x03) != 0ULL) {
        vSum += CountOnes(*vpByte);
        ++vpByte;
        --vResidue;
    }
    uint64_t *vpQWord = reinterpret_cast<uint64_t *>(vpByte);
    while(vResidue >= 8) {
        vSum += CountOnes(*vpQWord);
        ++vpQWord;
        --vResidue;
    }
    vpByte = reinterpret_cast<uint8_t *>(vpQWord);
    while(vResidue > 0) {
        vSum += CountOnes(*vpByte);
        ++vpByte;
        --vResidue;
    }
    return vSum;
}

class CountOnes
{
public:
    static constexpr int Result(uint64_t inVal)
    {
        int vSum = 0;
        uint64_t vResidue = inVal;
        while (vResidue > 0) {
            vSum += mResultOfByte[vResidue & 0xFF];
            vResidue >>= 8;
        }
        return vSum;
    }

    static constexpr int Result(uint8_t inVal[], int inCount)
    {
        int vSum = 0;
        int vResidue = inCount;
        while (vResidue > 0) {
            vSum += mResultOfByte[inVal[--vResidue]];
        }
        return vSum;
    }
private:
    //static constexpr int mResultOfByte[256];
    static constexpr int mResultOfByte[256] = {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
    };
};
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
