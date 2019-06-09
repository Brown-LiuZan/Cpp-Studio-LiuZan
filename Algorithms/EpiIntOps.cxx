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
#include <limits>
#include <stdexcept>

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

void SwapBits(uint64_t &bits, int i, int j)
{
    const uint64_t MASK_ITH = static_cast<uint64_t>(1) << i;
    const uint64_t MASK_JTH = static_cast<uint64_t>(1) << j;

    uint64_t bit_i = bits & MASK_ITH;
    bits &= ~MASK_ITH;
    uint64_t bit_j = bits & MASK_JTH;
    bits &= ~MASK_JTH;

    bit_i >>= i;
    bit_j >>= j;
    bits |= bit_j << i;
    bits |= bit_i << j;
}

void SwapBitsEfficiently(uint64_t &bits, int i, int j)
{
    const uint64_t MASK_ITH = static_cast<uint64_t>(1) << i;
    const uint64_t MASK_JTH = static_cast<uint64_t>(1) << j;
    const uint64_t MASK = MASK_ITH | MASK_JTH;

    if (((bits & MASK_ITH) >> i) != ((bits & MASK_JTH) >> j)) {
        bits ^= MASK;
    }
}

TEST(TSEpiIntOps, TCSwapBits)
{
    const int MAX_LOOP = 1000000;
    //const int MAX_LOOP = 1000;
    //const int MAX_LOOP = 1;
    uint64_t vBits;
    auto vStart = chrono::steady_clock::now();
    for (int loop = 0; loop < MAX_LOOP; ++loop) {
        for (int i = 0, j = 63; i < 63; ++i, --j) {
            vBits = static_cast<uint64_t>(1) << i;
            SwapBits(vBits, i, j);
            EXPECT_EQ(static_cast<uint64_t>(1) << j, vBits);
        }
    }
    auto vEnd = chrono::steady_clock::now();
    chrono::duration<double> vSecs = vEnd - vStart;
    std::cout << "SwapBits(): " << vSecs.count() << "s\n";
    std::cout << std::endl;

    vStart = chrono::steady_clock::now();
    for (int loop = 0; loop < MAX_LOOP; ++loop) {
        for (int i = 0, j = 63; i < 63; ++i, --j) {
            vBits = static_cast<uint64_t>(1) << i;
            SwapBitsEfficiently(vBits, i, j);
            EXPECT_EQ(static_cast<uint64_t>(1) << j, vBits);
        }
    }
    vEnd = chrono::steady_clock::now();
    vSecs = vEnd - vStart;
    std::cout << "SwapBits(): " << vSecs.count() << "s\n";
}

void ReverseBits(uint64_t &bits)
{
    static const uint8_t REVERSED_BITS[256] = {
		0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
		0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
		0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
		0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
		0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
		0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
		0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
		0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
		0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
		0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
		0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
		0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
		0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
		0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
		0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
		0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
		0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
		0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
		0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
		0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
		0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
		0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
		0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
		0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
		0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
		0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
		0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
		0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
		0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
		0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
		0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
		0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
	};

//#define REVERSE_BITS_GENERATE_TABLE
#ifdef REVERSE_BITS_GENERATE_TABLE
    std::cout << bits << std::endl;
    uint64_t vBits;
    for (uint64_t i = 0; i < 256; ++i) {
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        vBits = i;
        for (int j = 0, k = 7; j < 4; ++j, --k) {
            SwapBitsEfficiently(vBits, j, k);
        }
        std::cout << "0x" << std::setw(2) << std::setfill('0') << std::hex
            << vBits << ", ";
    }
    std::cout << std::endl;
#else //!defined(REVERSE_BITS_GENERATE_TABLE)
	union Bytes {
		uint64_t mQWord;
		uint8_t mBytes[8];
	};

	Bytes vRawBytes;
	Bytes vReversedBytes;
	vRawBytes.mQWord = bits;
	for (int i = 0, j = 7; i < 8; ++i, --j) {
		vReversedBytes.mBytes[i] = REVERSED_BITS[vRawBytes.mBytes[j]];
	}
	bits = vReversedBytes.mQWord;
#endif //REVERSE_BITS_GENERATE_TABLE
#ifdef REVERSE_BITS_GENERATE_TABLE
#undef REVERSE_BITS_GENERATE_TABLE
#endif
}

TEST(TSEpiIntOps, TCReverseBits)
{
	uint64_t vBits = 0xA5A555AAAA555A5AULL;
    ReverseBits(vBits);
	EXPECT_EQ(0x5A5AAA5555AAA5A5ULL, vBits);
}

uint64_t FindClosedIntegerWithSameOnes(uint64_t val)
{
    uint64_t vFlipBit1 = static_cast<uint64_t>(-1);
    uint64_t vFlipBits = 0;

    if (0 == val || vFlipBit1 == val) {
        return val;
    }

    if (val & 1) {
        uint64_t vReversed = ~val;
        vFlipBit1 = vReversed & ~(vReversed - 1);
    } else {
        vFlipBit1 = val & ~(val -1);
    }
    vFlipBits = vFlipBit1 | (vFlipBit1 >> 1);
    return val ^ vFlipBits;
}

TEST(TSEpiIntOps, TCFindClosedIntegerWithSameOnes)
{
    uint64_t vIn1 = 0xFFFFFFFCULL;
    uint64_t vOut1 = 0xFFFFFFFAULL;
    uint64_t vIn2 = 0xFFFFFFCFULL;
    uint64_t vOut2 = 0xFFFFFFD7ULL;
    EXPECT_EQ(vOut1, FindClosedIntegerWithSameOnes(vIn1));
    EXPECT_EQ(vOut2, FindClosedIntegerWithSameOnes(vIn2));
}

uint64_t Multiply(uint64_t a, uint64_t b)
{
    constexpr uint64_t HALF_MAX = std::numeric_limits<uint64_t>::max();

    uint64_t vResult = 0;
    uint64_t vResultOld = 0;
    uint64_t vWeighted = a;
    uint64_t vCoef = b;
    while (vCoef != 0) {
        if ((vCoef & 1) != 0) {
            vResultOld = vResult;
            vResult += vWeighted;
        }
        vCoef >>= 1;
        if (vWeighted > HALF_MAX || vResult < vResultOld) {
            throw std::out_of_range("Unsigned multiply overflow.");
        }
        vWeighted <<= 1;
    }

    return vResult;
}

int64_t Multiply(int64_t a ,int64_t b)
{
    bool vIsNeg_a = false;
    bool vIsNeg = false;
    if (a < 0) {
        vIsNeg_a = true;
        a = -a;
    }
    if (b < 0) {
        b = -b;
        if (true != vIsNeg_a) {
            vIsNeg = true;
        }
    } else {
        if (true == vIsNeg_a) {
            vIsNeg = true;
        }
    }
    try {
        const int64_t INT_MAX = std::numeric_limits<int64_t>::max();
        uint64_t vMid = Multiply(static_cast<uint64_t>(a),
                static_cast<uint64_t>(b));
        if ((!vIsNeg && vMid > static_cast<uint64_t>(INT_MAX)) ||
            (vIsNeg && vMid > static_cast<uint64_t>(INT_MAX) + 1)) {
            throw std::out_of_range("Signed multiply overflow.");
        }
        return vIsNeg ? static_cast<int64_t>((~vMid) + 1) :
            static_cast<int64_t>(vMid);
    } catch(const std::out_of_range & e) {
        std::cout << e.what() << std::endl;
        throw std::out_of_range("Signed multiply overflow.");
    }
}

TEST(TSEpiIntOps, TCMultiply)
{
    uint64_t a = 13579;
    uint64_t b = 24680;
    EXPECT_EQ(a * b, Multiply(a, b));
    try {
        b = 0xF0000000F0000000ULL;
        Multiply(a, b);
    } catch(const std::out_of_range &e) {
        std::cout << e.what() << std::endl;
    }

    int64_t c = 13579;
    int64_t d = -24680;
    EXPECT_EQ(c * d, Multiply(c, d));
    try {
        c = static_cast<int64_t>(0x7f000000F0000000ULL);
        Multiply(c, d);
    } catch(const std::out_of_range &e) {
        std::cout << e.what() << std::endl;
    }
}

uint64_t Divide(uint64_t a, uint64_t b)
{
    constexpr uint64_t HALF_MAX = std::numeric_limits<uint64_t>::max() >> 1;
    const uint64_t HALF_a = a >> 1;

    if (0 == b) {
        throw std::out_of_range("Unsigned divide by zero.");
    }

    uint64_t vResult = 0;
    uint64_t vItem = 1;
    uint64_t vWeighted = b;
    while (vWeighted <= HALF_a && vWeighted <= HALF_MAX) {
        vItem <<= 1;
        vWeighted <<= 1;
    }
    vResult += vItem;
    uint64_t vRedius = a - vWeighted;
    while (vRedius != 0 && vItem != 0) {
        vItem >>= 1;
        vWeighted >>= 1;
        if (vRedius > vWeighted) {
            vResult += vItem;
            vRedius -= vWeighted;
        }
    }
    return vResult;
}

int64_t Divide(int64_t a, int64_t b)
{
    if (0 == b) {
        throw std::out_of_range("Signed divide by zero.");
    }

    bool vIsNeg_a = false;
    bool vIsNeg = false;
    if (a < 0) {
        vIsNeg_a = true;
        a = -a;
    }
    if (b < 0) {
        b = -b;
        if (!vIsNeg_a) {
            vIsNeg = true;
        }
    } else {
        if (vIsNeg_a) {
            vIsNeg = true;
        }
    }
    uint64_t vMid = Divide(static_cast<uint64_t>(a),
                           static_cast<uint64_t>(b));
    return vIsNeg ? static_cast<int64_t>(~vMid + 1) :
        static_cast<int64_t>(vMid);
}

TEST(TSEpiIntOps, TCDivide)
{
    uint64_t a = 0xF034123401234567ULL;
    uint64_t b = 1123;
    EXPECT_EQ(a / b, Divide(a, b));
    try {
        Divide(b, 0);
    } catch(const std::out_of_range & e) {
        std::cout << e.what() << std::endl;
    }

    int64_t c = -1357924680LL;
    int64_t d = 2478;
    EXPECT_EQ(c / d, Divide(c, d));
    try {
        Divide(c, 0);
    } catch(const std::out_of_range & e) {
        std::cout << e.what() << std::endl;
    }
}

#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
