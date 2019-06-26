#include <gtest/gtest.h>

#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <limits>

using namespace testing;

template<typename T>
std::pair<size_t, size_t> DutchNationalFlag(std::vector<T> &vec, T mark)
{
    size_t vSmallerUpper = 0; //Also EqualLower
    size_t vEqualUpper  = 0;
    size_t vLargerLower = vec.size();

    while (vEqualUpper < vLargerLower) {
        if (vec[vEqualUpper] < mark) {
            std::swap(vec[vSmallerUpper], vec[vEqualUpper]);
            ++vSmallerUpper;
            ++vEqualUpper;
        } else if (vec[vEqualUpper] > mark) {
            --vLargerLower;
            std::swap(vec[vLargerLower], vec[vEqualUpper]);
        } else {
            ++vEqualUpper;
        }
    }

    return std::make_pair(vSmallerUpper, vEqualUpper);
}

TEST(TSEpiArray, TCDutchNationalFlag)
{
    std::vector<int> vVec{1, 3, -1, 3, 2, 4, 8, -2};
    std::cout << "Before partition: ";
    for (auto x : vVec) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    auto vBds = DutchNationalFlag(vVec, 3);
    std::cout << "After partition: ";
    for (auto x : vVec) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    EXPECT_EQ(4, vBds.first);
    EXPECT_EQ(6, vBds.second);
    size_t i = 0;
    while (i < vBds.first) {
        EXPECT_GT(3, vVec[i]);
        ++i;
    }
    while (i < vBds.second) {
        EXPECT_EQ(3,vVec[i]);
        ++i;
    }
    while (i < vVec.size()) {
        EXPECT_LT(3, vVec[i]);
        ++i;
    }
}

class Integer
{
    friend bool operator ==(const Integer & a, const Integer & b);
    friend bool operator < (const Integer & a, const Integer & b);
    friend bool operator ==(int64_t a, const Integer & b);
    friend bool operator < (int64_t a, const Integer & b);
    friend Integer operator * (const Integer & a, const Integer & b);

public:
    Integer():
        mIsNegative(false)
    {
    }
    explicit Integer(int64_t val)
    {
        if (val < 0) {
            mIsNegative = true;
            val = -val;
        } else {
            mIsNegative = false;
        }
        while (val != 0) {
            mDigits.push_back(val % BASE);
            val /= BASE;
        }
    }
    Integer(const Integer & origin) = default;
    Integer & operator = (const Integer & origin) = default;
    Integer & operator = (int64_t val)
    {
        *this = Integer(val);
        return *this;
    }

    Integer & operator++()
    {
        if (mIsNegative) {
            digitsMinusOne();
            if (0 == mDigits.size()) {
                mIsNegative = false;
            }
        } else {
            digitsPlusOne();
        }
        return *this;
    }
    Integer operator++(int)
    {
        Integer vRtn(*this);
        ++(*this);
        return vRtn;
    }
    Integer & operator--()
    {
        if (mIsNegative) {
            digitsPlusOne();
        } else if (0 == mDigits.size()) {
            mDigits.push_back(1);
            mIsNegative = true;
        } else {
            digitsMinusOne();
        }
        return *this;
    }
    Integer operator--(int)
    {
        Integer vRtn(*this);
        --(*this);
        return vRtn;
    }

    operator int64_t () const
    {
        const uint64_t INT64_MIN_MAGNITUDE =
            ~static_cast<uint64_t>(std::numeric_limits<int64_t>::min()) + 1;
        const uint64_t INT64_MAX_MAGNITUDE =
            std::numeric_limits<int64_t>::max();

        uint64_t vMagnitude = 0;
        uint64_t vItem = 1;

        if (mDigits.size() > sizeof(uint64_t)) {
            throw std::out_of_range("int64_t overflow");
        }

        for (size_t i = 0; i < mDigits.size(); ++i) {
            vMagnitude += vItem * mDigits[i];
            vItem *= BASE;
        }

        if (mIsNegative && vMagnitude > INT64_MIN_MAGNITUDE) {
            throw std::out_of_range("int64_t overflow");
        } else if (!mIsNegative && vMagnitude > INT64_MAX_MAGNITUDE) {
            throw std::out_of_range("int64_t overflow");
        }

        return mIsNegative ? -vMagnitude : vMagnitude;
    }

private:
    void digitsPlusOne()
    {
        uint16_t vSum = 1;
        for (size_t i = 0; i < mDigits.size(); ++i)
        {
            vSum += mDigits[i];
            if (BASE == vSum) {
                mDigits[i] = 0;
                vSum = 1;
            } else {
                mDigits[i] = vSum;
                vSum = 0;
                break;
            }
        }
        if (0 != vSum) {
            mDigits.push_back(1);
        }
    }

    void digitsMinusOne()
    {
        for (size_t i = 0; i < mDigits.size(); ++i)
        {
            if (0 == mDigits[i]) {
                mDigits[i] = 255;
            } else {
                --mDigits[i];
                break;
            }
        }
        if (0 == *mDigits.rbegin()) {
            mDigits.pop_back();
        }
    }

    static const uint16_t BASE = 256;
    std::vector<uint8_t> mDigits;
    bool mIsNegative;
};

bool operator == (const Integer & a, const Integer & b)
{
    if (a.mIsNegative != b.mIsNegative) {
         return false;
    } else if (a.mDigits.size() != b.mDigits.size()) {
        return false;
    } else {
        for (size_t i = 0; i < a.mDigits.size(); ++i) {
            if (a.mDigits[i] != b.mDigits[i]) {
                return false;
            }
        }
        return true;
    }
}

bool operator != (const Integer & a, const Integer & b)
{
    return !(a == b);
}

bool operator < (const Integer & a, const Integer & b)
{
    if (!a.mIsNegative && b.mIsNegative) {
        return false;
    } else if (a.mIsNegative && !b.mIsNegative) {
        return true;
    } else if (a.mDigits.size() < b.mDigits.size()) {
        return a.mIsNegative ? false : true;
    } else if (a.mDigits.size() > b.mDigits.size()) {
        return a.mIsNegative ? true : false;
    } else if (a.mIsNegative) {
        return std::lexicographical_compare(
                a.mDigits.rbegin(), a.mDigits.rend(),
                b.mDigits.rbegin(), b.mDigits.rend(),
                std::greater<uint8_t>());
    } else {
        return std::lexicographical_compare(
                a.mDigits.rbegin(), a.mDigits.rend(),
                b.mDigits.rbegin(), b.mDigits.rend(),
                std::less<uint8_t>());
    }
}

Integer operator * (const Integer & a, const Integer & b)
{
    Integer vProduct;

    if (0 == a.mDigits.size() || 0 == b.mDigits.size()) {
        return vProduct;
    }
    vProduct.mDigits.resize(a.mDigits.size() + b.mDigits.size(), 0);
    vProduct.mIsNegative = a.mIsNegative ^ b.mIsNegative;

    uint16_t vUint8Product = 0;
    for (size_t i = 0; i < a.mDigits.size(); ++i) {
        for (size_t j = 0; j < b.mDigits.size(); ++j) {
            vUint8Product = a.mDigits[i] * b.mDigits[j];
            for (size_t k = i + j; k < vProduct.mDigits.size(); ++k) {
                vUint8Product += vProduct.mDigits[k];
                if (Integer::BASE > vUint8Product) {
                    vProduct.mDigits[k] = vUint8Product;
                    break;
                } else {
                    vProduct.mDigits[k] = vUint8Product % Integer::BASE;
                    vUint8Product /= Integer::BASE;
                }
            }
        }
    }

    for (int64_t  k = static_cast<int64_t>(vProduct.mDigits.size()) - 1;
            k >= 0; --k) {
        if (0 != vProduct.mDigits[k]) {
            ++k;
            vProduct.mDigits.resize(k);
            break;
        }
    }

    return vProduct;
}

TEST(TSEpiArray, TCInteger)
{
    Integer vInteger{};
    EXPECT_TRUE(0 == static_cast<int64_t>(vInteger));
    EXPECT_TRUE(1 == static_cast<int64_t>(++vInteger));
    EXPECT_TRUE(1 == static_cast<int64_t>(vInteger++));
    EXPECT_TRUE(2 == static_cast<int64_t>(vInteger));
    EXPECT_TRUE(1 == static_cast<int64_t>(--vInteger));
    EXPECT_TRUE(1 == static_cast<int64_t>(vInteger--));
    EXPECT_TRUE(0 == static_cast<int64_t>(vInteger));
    EXPECT_TRUE(-1 == static_cast<int64_t>(--vInteger));
    EXPECT_TRUE(-1 == static_cast<int64_t>(vInteger--));
    EXPECT_TRUE(-2 == static_cast<int64_t>(vInteger));
    vInteger = -278;
    EXPECT_TRUE(-278 == static_cast<int64_t>(vInteger));
    vInteger = 278;
    EXPECT_TRUE(278 == static_cast<int64_t>(vInteger));

    Integer a{-1234};
    Integer b(4321);
    Integer c = a * b;
    EXPECT_EQ(-1234 * 4321, static_cast<int64_t>(c));
}
