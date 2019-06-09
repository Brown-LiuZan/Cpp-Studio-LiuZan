#include <vector>
#include <iterator> // std::distance, std::begin, std::end
#include <utility> // std::swap
#include <algorithm> // std::shuffle
#include <random> // std::random_device, std::mt19937
#include <chrono> // std::duration
#include <iostream>

#include <gtest/gtest.h>

template<typename RandomAccessIterator>
void QuickSort(RandomAccessIterator first, RandomAccessIterator last)
{
    // Judge if continuing or not.
    if (std::distance(first, last) < 2) {
        return;
    }

    // Partition
    RandomAccessIterator vLow = first;
    RandomAccessIterator vMid = first + std::distance(first, last) / 2;
    RandomAccessIterator vHigh = last;
    std::swap(*vLow, *vMid); // Choose the midpoint as partitioning point
    do {
        // Find first pair to swap
        while (vLow < vHigh && *(++vLow) <= *first) {}
        while (vHigh > vLow && *(--vHigh) >= *first) {}
        // Swap the found pair
        if (vLow < vHigh) {
            std::swap(*vLow, *vHigh);
        }
    } while (vLow < vHigh);

    // Recursively sort partitioned small elments and large elements.
    QuickSort(first, vLow);
    QuickSort(vLow, last);
}

TEST(TSSort, TCQuickSort)
{
    const int CONTAINER_CAPACITY = 1024 * 1024;
    const int PRINT_MAX = 8;
    std::vector<int> vVec;
    int vArr[CONTAINER_CAPACITY];
    vVec.resize(CONTAINER_CAPACITY);
    for (int i = 0; i < CONTAINER_CAPACITY; ++i) {
        vVec[i] = vArr[i] = i;
    }
    std::random_device vRd;
    std::mt19937 vUrng(vRd());
    std::shuffle(vVec.begin(), vVec.end(), vUrng);
    std::shuffle(std::begin(vArr), std::end(vArr), vUrng);
    std::cout << "After shuffle and before sort:" << std::endl;
    std::cout << "vector<int>[0, 8): " << std::endl;
    int vCnt = 0;
    for (auto i : vVec) {
        if (vCnt++ < PRINT_MAX) {
            std::cout << i << " ";
        } else {
            break;
        }
    }
    std::cout << std::endl;
    std::cout << "int[][0, 8)" << std::endl;
    vCnt = 0;
    for (auto i : vArr) {
        if (vCnt++ < PRINT_MAX) {
            std::cout << i << " ";
        } else {
            break;
        }
    }
    std::cout << std::endl;

    auto vStart = std::chrono::steady_clock::now();
    QuickSort(vVec.begin(), vVec.end());
    auto vEnd = std::chrono::steady_clock::now();
    std::chrono::duration<double> vLatency = vEnd - vStart;
    std::cout << "Time consumed by sorting vec: " << vLatency.count()
        << "secs." << std::endl;
    vStart = std::chrono::steady_clock::now();
    QuickSort(std::begin(vArr), std::end(vArr));
    vEnd = std::chrono::steady_clock::now();
    vLatency = vEnd - vStart;
    std::cout << "Time consumed by sorting array: " << vLatency.count()
        << "secs." << std::endl;

    std::cout << "After sort:" << std::endl;
    std::cout << "vector<int>[0, 8): " << std::endl;
    int vVal = 0;
    vCnt = 0;
    for (auto i : vVec) {
        if (vCnt++ < PRINT_MAX) {
            std::cout << i << " ";
        }
        EXPECT_EQ(vVal, i);
        ++vVal;
    }
    std::cout << std::endl;
    std::cout << "int[][0, 8)" << std::endl;
    vVal = 0;
    vCnt = 0;
    for (auto i : vArr) {
        if (vCnt++ < PRINT_MAX) {
            std::cout << i << " ";
        }
        EXPECT_EQ(vVal, i);
        ++vVal;
    }
    std::cout << std::endl;
}
