#include <vector>
#include <limits>
#include <iostream>
#include <stdexcept>

#include <gtest/gtest.h>

#include "Common/cxx_version_macroes.h"

using namespace std;

TEST(TSStdVector, TCCtorAssign)
{
    {//1.Default constructor
        //vector<int> vVec(); //Error, a function declaration from C++11.
        vector<int> vVec;
        EXPECT_EQ(0, vVec.size());
        EXPECT_EQ(0, vVec.capacity());
    }
    {//2.Counter constructor
#if __cplusplus > CPLUSPLUS_VAL_FOR_98
        //vector<int> vVec{7}; //Error, initializer-list initialized.
        vector<int> vVec(7);
        // Defauted constructed, no trust on values.
        EXPECT_EQ(7, vVec.size());
        EXPECT_EQ(7, vVec.capacity());
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
    }
    {//3.Counter and value constructor
        //vector<int> vVec{3, 3}; //Error, initializer-list initialized.
        vector<int> vVec(3, 3);
        EXPECT_EQ(3, vVec.size());
        EXPECT_EQ(3, vVec.capacity());
        for (auto i : vVec) {
            EXPECT_EQ(3, i);
        }
        //vVec[3] = 6; // Bug with undefined behavior.
        vVec.push_back(4);
        EXPECT_EQ(4, vVec.size());
        EXPECT_EQ(6, vVec.capacity());

        vVec.assign(14, 14);
        EXPECT_EQ(14, vVec.size());
        EXPECT_EQ(14, vVec.capacity());
    }
    {//4.Range constructor with given range [begin, end).
        vector<int> vVec(9);
        int vVal = 0;
        for (auto &e : vVec) {
            e = vVal;
            ++vVal;
        }
        vector<int> vCopy(vVec.begin(), vVec.end());
        EXPECT_EQ(vVec.capacity(), vCopy.size());
        vVal = 0;
        for (auto e : vCopy) {
            EXPECT_EQ(vVal, e);
            ++vVal;
        }

        vector<int> vCopy2(199, 199);
        vCopy2.assign(vVec.begin(), vVec.end());
        EXPECT_EQ(vVec.size(), vCopy2.size());
        EXPECT_EQ(199, vCopy2.capacity());
        vVal = 0;
        for (auto e : vCopy2) {
            EXPECT_EQ(vVal, e);
            ++vVal;
        }
    }
    {//5.Copy constructor
        vector<int> vOrigin(4, 7);
        vOrigin.push_back(7);
        EXPECT_EQ(5, vOrigin.size());
        EXPECT_EQ(8, vOrigin.capacity());
        vector<int> vCopy(vOrigin);
        EXPECT_EQ(vOrigin.size(), vCopy.size());
        EXPECT_EQ(vOrigin.size(), vCopy.capacity())
            << "It's expected that no more space is allocated than needed"
            << " during copy construction.";
        for (auto e : vCopy) {
            EXPECT_EQ(7, e);
        }

        vCopy.resize(4);
        EXPECT_EQ(4, vCopy.size());
        //Decreasing resize() and reserve() won't change capacity.
        EXPECT_EQ(5, vCopy.capacity());
        vCopy.shrink_to_fit();
        EXPECT_EQ(4, vCopy.capacity());
        for (auto &e : vCopy) {
            e = 2;
        }
        vCopy.push_back(2);
        EXPECT_EQ(5, vCopy.size());
        EXPECT_EQ(8, vCopy.capacity());
        vector<int> vCopy2_1(16, 16);
        vector<int> vCopy2_2;
        vCopy2_1 = vCopy;
        EXPECT_EQ(5, vCopy2_1.size());
        EXPECT_EQ(16, vCopy2_1.capacity())
            << "It's expected that size will be reset and capacity won't be"
            << " shrinked during copy assignment.";
        vCopy2_2 = vCopy;
        EXPECT_EQ(5, vCopy2_2.size());
        EXPECT_EQ(5, vCopy2_2.capacity())
            << "It's expected no more space is allocated newly than needed"
            << " during copy assignment.";
        for (auto e : vCopy2_1) {
            EXPECT_EQ(2, e);
        }
        //At most one allocation of memory during copy construction/assignment.
    }
    {//6.Move constructor
#if __cplusplus > CPLUSPLUS_VAL_FOR_98
        vector<int> vMove(vector<int>(4, 7));
        EXPECT_EQ(4, vMove.size());
        EXPECT_EQ(4, vMove.capacity());
        for (auto e : vMove) {
            EXPECT_EQ(7, e);
        }
        vMove.push_back(8);
        EXPECT_EQ(5, vMove.size());
        EXPECT_EQ(8, vMove.capacity());
        vector<int> vMove2 = move(vMove);
        EXPECT_EQ(5, vMove2.size());
        EXPECT_EQ(8, vMove2.capacity());
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
    }
    {//7.Initializer-list constructor
#if __cplusplus > CPLUSPLUS_VAL_FOR_98
        vector<int> vList{1, 2, 3, 4, 5, 6};
        EXPECT_EQ(6, vList.size());
        EXPECT_EQ(6, vList.capacity());
        int i = 1;
        for (auto e : vList) {
            EXPECT_EQ(i, e);
            ++i;
        }

        vList = {7, 8};
        EXPECT_EQ(2, vList.size());
        EXPECT_EQ(6, vList.capacity());

        vList.assign({9, 8, 7, 6, 5, 4, 3, 2, 1});
        EXPECT_EQ(9, vList.size());
        EXPECT_EQ(9, vList.capacity());
        int vVal = 9;
        for (auto e : vList) {
            EXPECT_EQ(vVal, e);
            --vVal;
        }
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
    }
}

TEST(TSStdVector, TCCapacity)
{
    vector<int> vVec;
    EXPECT_EQ(0, vVec.size());
    EXPECT_EQ(0, vVec.capacity())
        << "It's expected to be 0 for both size and capacity of the default"
        << " construced vector.";

    for (int i = 0; i < 16; ++i) {
        vVec.push_back(i);
    }
    EXPECT_EQ(16, vVec.size());
    EXPECT_EQ(16, vVec.capacity())
        << "It's expected to be 16 for both size and capacity after inserting"
        << " 16 integers into vector.";

    vVec.push_back(16);
    EXPECT_EQ(17, vVec.size());
    EXPECT_EQ(32, vVec.capacity())
        << "It's expected to be 17 for size after inserting 17 integers into"
        << " vector and 32 for capacity.";

    vVec.reserve(16);
    EXPECT_EQ(17, vVec.size());
    EXPECT_EQ(32, vVec.capacity())
        << "It's expected no change for both size and capacity if reserving"
        << " less than size or capacity.";

    vVec.reserve(64);
    EXPECT_EQ(17, vVec.size());
    EXPECT_EQ(64, vVec.capacity())
        << "It's expected no change of size and increasement of capacity if"
        << " reserving more space than capacity.";

    vVec.resize(8);
    EXPECT_EQ(8, vVec.size());
    EXPECT_EQ(64, vVec.capacity())
        << "It's expected no change of capacity and change of size if resizing"
        << " vector.";

#if __cplusplus > CPLUSPLUS_VAL_FOR_98
    vVec.resize(16);
    vVec.shrink_to_fit();
    EXPECT_EQ(16, vVec.size());
    EXPECT_EQ(16, vVec.capacity())
        << "It's exptected shrinking will make size equel to capacity.";
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98

    vVec.resize(33);
    EXPECT_EQ(33, vVec.size());
    EXPECT_EQ(33, vVec.capacity())
        << "It's expected resize() set both size and capacity to given value.";

    if (8 == sizeof(void *)) {
        EXPECT_LT(numeric_limits<unsigned int>::max(), vVec.max_size());
        EXPECT_GT(numeric_limits<long long>::max(), vVec.max_size())
            << "It's expected vector could hold less elements than"
            << " numeric_limit<long long>::max() and more than"
            << " numeric_limit<unsigned int>::max() on x64.";
    } else {
        EXPECT_LT(numeric_limits<unsigned short>::max(), vVec.max_size());
        EXPECT_GT(numeric_limits<long>::max(), vVec.max_size())
            << "It's expected vector could hold less elements than"
            << " numeric_limit<int>::max() and more than"
            << " numeric_limit<unsigned short>::max() on x86.";
    }
}

TEST(TSStdVector, TCAccess)
{
    vector<int> vVec;
    for ( int i = 0; i < 10; ++i) {
        vVec.push_back(i);
    }
    try {
        EXPECT_EQ(5, vVec.at(5));
        vVec.at(11);
    } catch (out_of_range const &e) {
        cout << e.what() << endl;
        cout << "vVec[5]: " << vVec[5]
             << " vVec[11]: " << vVec[11] << endl;
    }
    EXPECT_EQ(0, vVec.front());
    EXPECT_EQ(vVec.size() - 1, vVec.back());
#if __cplusplus > CPLUSPLUS_VAL_FOR_98
    int *vpData = vVec.data();
    for (int i = 0; i < static_cast<int>(vVec.size()); ++i) {
        EXPECT_EQ(i, *vpData);
        ++vpData;
    }
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
}

TEST(TSStdVector, TCIterator)
{
    vector<int> vVec(10, 1);
    int vSum = 0;
    for (vector<int>::iterator it = vVec.begin(); it != vVec.end(); ++it) {
        vSum += *it;
        *it = vSum;
    }
    EXPECT_EQ(vVec.size(), vSum);
    int vVal = 10;
    for (vector<int>::reverse_iterator it = vVec.rbegin();
            it != vVec.rend();
            ++it) {
        EXPECT_EQ(vVal, *it);
        --vVal;
    }
#if __cplusplus > CPLUSPLUS_VAL_FOR_98
    vVal = 1;
    for (auto it = vVec.cbegin(); it != vVec.cend(); ++it) {
        EXPECT_EQ(vVal, *it);
        ++vVal;
    }
    vVal = 10;
    for (auto it = vVec.crbegin(); it != vVec.crend(); ++it) {
        EXPECT_EQ(vVal, *it);
        --vVal;
    }
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
    const vector<int> vCopy(vVec);
    vVal = 1;
    for (vector<int>::const_iterator it = vCopy.begin();
            it != vCopy.end();
            ++it) {
        EXPECT_EQ(vVal, *it);
        ++vVal;
    }
    vVal = 10;
    for (vector<int>::const_reverse_iterator it = vCopy.rbegin();
            it != vCopy.rend();
            ++it) {
        EXPECT_EQ(vVal, *it);
        --vVal;
    }
}

TEST(TSStdVector, TCModifiers)
{
    vector<int> vVec;
    vVec.reserve(10);
    vVec.resize(6);
    int vVal = 2;
    for (size_t i = 0; i < 6; ++i) {
        vVec[i] = vVal;
        ++vVal;
    }
#if __cplusplus > CPLUSPLUS_VAL_FOR_98
    auto vIt1 = vVec.cbegin();
    vVec.insert(vIt1, 1);
    vIt1 = vVec.cbegin();
    vVec.emplace(vIt1, 0);
    vVec.push_back(8);
    vVec.emplace_back(9);
    EXPECT_EQ(10, vVec.size());
    vVal = 0;
    for (auto e : vVec) {
        EXPECT_EQ(vVal, e);
        ++vVal;
    }
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_98
    vector<int>::iterator vIt2= vVec.erase(vVec.begin());
    vIt2 += 3;
    vVec.erase(vVec.begin(), vIt2);
    EXPECT_EQ(6, vVec.size());
    vVec.pop_back();
    EXPECT_EQ(5, vVec.size());
    EXPECT_EQ(10, vVec.capacity());
    vIt2 = vVec.end();
    --vIt2;
    EXPECT_EQ(8, *vIt2);
    vector<int> vCopy;
    vCopy.swap(vVec);
    EXPECT_EQ(8, *vIt2);
    EXPECT_EQ(0, vVec.size());
    EXPECT_EQ(0, vVec.capacity());
    EXPECT_EQ(5, vCopy.size());
    EXPECT_EQ(10, vCopy.capacity());
    vCopy.clear();
    EXPECT_EQ(0, vCopy.size());
    EXPECT_EQ(10, vCopy.capacity());
}

#if __cplusplus > CPLUSPLUS_VAL_FOR_17
TEST(TSStdVector, TCEraseAlgorithm)
{
    vector<int> vVec;
    vVec.reserve(100);
    for (int i = 0; i < 100; ++i) {
        vVec.push_back(i);
    }
    EXPECT_EQ(100, vVec.size());
    erase(vVec, 44);
    EXPECT_EQ(99, vVec.size());
    auto GreaterThan44 = [](int i) { return i > 44; };
    erase_if(vVec, GreaterThan44);
    EXPECT_EQ(44, vVec.size());
}
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_17

#if __cplusplus > CPLUSPLUS_VAL_FOR_14
/**
 * For std::pmr::vector<>
 */
#endif // __cplusplus > CPLUSPLUS_VAL_FOR_14
