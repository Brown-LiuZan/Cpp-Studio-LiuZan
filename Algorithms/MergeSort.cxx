#include <list>
#include <vector>
#include <iterator> // std::distance, std::begin, std::end
#include <utility> // std::swap
#include <algorithm> // std::shuffle
#include <random> // std::random_device, std::mt19937
#include <chrono> // std::duration
#include <iostream>

#include <gtest/gtest.h>

#include "Common/assert.h"

template<typename T>
bool mergeSortSharedAuxInternal(
        std::vector<T> &vec, std::vector<T> &vecAux,
        bool isDataInAux,
        size_t first, size_t last)
{
    if (first + 1 >= last) {
        return isDataInAux;
    }

    size_t vMid = (first + last) / 2;
    bool vIsDataInAux1 =
        mergeSortSharedAuxInternal(vec, vecAux, isDataInAux, first, vMid);
    bool vIsDataInAux2 =
        mergeSortSharedAuxInternal(vec, vecAux, isDataInAux, vMid, last);
    std::vector<T> &vecSrc = vIsDataInAux2 ? vecAux : vec;
    std::vector<T> &vecDes = vIsDataInAux2 ? vec : vecAux;
    if (vIsDataInAux1 != vIsDataInAux2) {
        std::copy(vecDes.begin() + first, vecDes.begin() + vMid,
                vecSrc.begin() + first);
    }

    size_t vCursorSrc1 = first;
    size_t vCursorSrc2 = vMid;
    size_t vCursorDes = first;
    do {
        if (vCursorSrc1 >= vMid) {
            std::copy(std::next(vecSrc.begin(), vCursorSrc2),
                    std::next(vecSrc.begin(), last),
                    std::next(vecDes.begin(), vCursorDes));
            vCursorDes = last;
        } else if (vCursorSrc2 >= last) {
            std::copy(std::next(vecSrc.begin(), vCursorSrc1),
                    std::next(vecSrc.begin(), vMid),
                    std::next(vecDes.begin(), vCursorDes));
            vCursorDes = last;
        } else {
            if (vecSrc[vCursorSrc1] > vecSrc[vCursorSrc2]) {
                vecDes[vCursorDes] = vecSrc[vCursorSrc2];
                ++vCursorSrc2;
            } else {
                vecDes[vCursorDes] = vecSrc[vCursorSrc1];
                ++vCursorSrc1;
            }
            ++vCursorDes;
        }
    } while(vCursorDes < last);
    return !vIsDataInAux2;
}

template<typename T>
void MergeSortSharedAux(std::vector<T> &vec)
{
    if (vec.size() < 2) {
        return;
    }

    std::vector<T> vVecAux(vec.size());
    bool vIsDataInAux = mergeSortSharedAuxInternal(
            vec, vVecAux, false, 0, vec.size());
    if (vIsDataInAux) {
        std::copy(vVecAux.begin(), vVecAux.end(), vec.begin());
    }
}

template<typename T>
void mergeSortNoSharedAuxInternal(
        std::vector<T> &vec, size_t first, size_t last)
{
    if (first + 1 >= last) {
        return;
    }

    size_t vMid = (first + last) / 2;
    mergeSortNoSharedAuxInternal(vec, first, vMid);
    mergeSortNoSharedAuxInternal(vec, vMid, last);

    std::vector<T> vecAux(last - first);
    size_t vSize = vecAux.size();
    size_t vCursorSrc1 = first;
    size_t vCursorSrc2 = vMid;
    size_t vCursorDes = 0;
    do {
        if (vCursorSrc1 >= vMid) {
            std::copy(vec.begin() + vCursorSrc2, vec.begin() + last,
                    vecAux.begin() + vCursorDes);
            vCursorDes = vSize;
        } else if (vCursorSrc2 >= last) {
            std::copy(vec.begin() + vCursorSrc1, vec.begin() + vMid,
                    vecAux.begin() + vCursorDes);
            vCursorDes = vSize;
        } else {
            if (vec[vCursorSrc1] > vec[vCursorSrc2]) {
                vecAux[vCursorDes] = vec[vCursorSrc2];
                ++vCursorSrc2;
            } else {
                vecAux[vCursorDes] = vec[vCursorSrc1];
                ++vCursorSrc1;
            }
            ++vCursorDes;
        }
    } while (vCursorDes < vSize);
    std::copy(vecAux.begin(), vecAux.end(), vec.begin() + first);
}

template<typename T>
void MergeSortNoSharedAux(std::vector<T> &vec)
{
    // Judge if continuing or not.
    if (vec.size() < 2) {
        return;
    }

    mergeSortNoSharedAuxInternal(vec, 0, vec.size());
}

template<typename T>
struct ListNode
{
    ListNode *mpNext;
    ListNode *mpPrev;
    T mData;

    ListNode():
        mpNext(this),
        mpPrev(this),
        mData()
    {}

    ListNode(const T &data):
        mpNext(this),
        mpPrev(this),
        mData(data)
    {}

    ~ListNode()
    {
        mpNext = mpPrev = nullptr;
    }

    void Append(ListNode *node)
    {
        ListNode *vpLocalNext = mpNext;
        ListNode *vpExternalTail = node->mpPrev;

        vpExternalTail->mpNext = vpLocalNext;
        node->mpPrev = this;
        mpNext = node;
        vpLocalNext->mpPrev = vpExternalTail;
    }

    void Prepend(ListNode *node)
    {
        ListNode *vpLocalTail = mpPrev;
        ListNode *vpExternalTail = node->mpPrev;

        node->mpPrev = vpLocalTail;
        vpExternalTail->mpNext = this;
        mpPrev = vpExternalTail;
        vpLocalTail->mpNext = node;
    }

    ListNode * Detach()
    {
        ListNode *vpNext = mpNext;
        vpNext->mpPrev = mpPrev;
        mpPrev->mpNext = vpNext;
        mpNext = mpPrev = this;
        return vpNext;
    }

    void AttachBefore(ListNode *successor)
    {
        ListNode *vpPredecessor = successor->mpPrev;
        mpNext = successor;
        mpPrev = vpPredecessor;
        successor->mpPrev = this;
        vpPredecessor->mpNext = this;
    }

    void AttachAfter(ListNode *predecessor)
    {
        ListNode *vpSuccessor = predecessor->mpNext;
        mpNext = vpSuccessor;
        mpPrev = predecessor;
        predecessor->mpNext = this;
        vpSuccessor->mpPrev = this;
    }
};

template<typename T>
void MergeSortList(ListNode<T> * &list)
{
    if (nullptr == list || list->mpNext == list) {
        return;
    }

    ListNode<T> *vpCursorSlow = list;
    ListNode<T> *vpCursorFast = list;
    bool isMoveSlowEnabled = true;
    while (vpCursorFast->mpNext != list) {
        if (isMoveSlowEnabled) {
            isMoveSlowEnabled = false;
            vpCursorSlow = vpCursorSlow->mpNext;
        } else {
            isMoveSlowEnabled = true;
        }
        vpCursorFast = vpCursorFast->mpNext;
    }
    ListNode<T> *vpOldTail = list->mpPrev;
    ListNode<T> *vpNewTail = vpCursorSlow->mpPrev;
    vpOldTail->mpNext = vpCursorSlow;
    vpCursorSlow->mpPrev = vpOldTail;
    vpNewTail->mpNext = list;
    list->mpPrev = vpNewTail;
    MergeSortList(list);
    MergeSortList(vpCursorSlow);

    ListNode<T> vMerged;
    ListNode<T> vFirstList;
    ListNode<T> vSecondList;
    vFirstList.Append(list);
    vSecondList.Append(vpCursorSlow);
    do {
        if (vFirstList.mpNext == &vFirstList) {
            vMerged.Prepend(vSecondList.Detach());
        } else if (vSecondList.mpNext == &vSecondList) {
            vMerged.Prepend(vFirstList.Detach());
        } else {
            ListNode<T> *vpFirstSmallest = vFirstList.mpNext;
            ListNode<T> *vpSecondSmallest = vSecondList.mpNext;
            if (vpFirstSmallest->mData > vpSecondSmallest->mData) {
                vpSecondSmallest->Detach();
                vMerged.Prepend(vpSecondSmallest);
            } else {
                vpFirstSmallest->Detach();
                vMerged.Prepend(vpFirstSmallest);
            }
        }
    } while (vFirstList.mpNext != &vFirstList ||
            vSecondList.mpNext != &vSecondList);
    list = vMerged.Detach();
    return;
}

TEST(TSSort, TCMergeSort)
{
    const int CONTAINER_CAPACITY = 100 * 1024 * 1024;
    //const int CONTAINER_CAPACITY = 1024 * 1024;
    //const int CONTAINER_CAPACITY = 8;
    const int PRINT_MAX = 8;
    std::vector<int> vVec;
    vVec.resize(CONTAINER_CAPACITY);
    int vVal = 0;
    while (vVal < CONTAINER_CAPACITY) {
        vVec[vVal] = vVal;
        ++vVal;
    }
    std::random_device vRd;
    std::mt19937 vUrng(vRd());

    std::shuffle(vVec.begin(), vVec.end(), vUrng);
    std::cout << "After shuffle and before sort:" << std::endl;
    std::cout << "vector<int>[0, " << PRINT_MAX << "): " << std::endl;
    int vCnt = 0;
    while (vCnt < PRINT_MAX) {
        std::cout << vVec[vCnt] << " ";
        ++vCnt;
    }
    std::cout << std::endl;
    auto vStart = std::chrono::steady_clock::now();
    MergeSortNoSharedAux(vVec);
    auto vEnd = std::chrono::steady_clock::now();
    std::chrono::duration<double> vLatency = vEnd - vStart;
    std::cout << "Time consumed by sorting vec with no shared aux algorithm: "
        << vLatency.count() << "secs." << std::endl;
    std::cout << "After sort:" << std::endl;
    std::cout << "vector<int>[0, " << PRINT_MAX << "): " << std::endl;
    vVal = 0;
    vCnt = 0;
    for (auto i : vVec) {
        if (vCnt < PRINT_MAX) {
            std::cout << vVec[vCnt] << " ";
            ++vCnt;
        }
        EXPECT_EQ(vVal, i);
        ++vVal;
    }
    std::cout << std::endl;

    std::cout << std::endl;
    std::shuffle(vVec.begin(), vVec.end(), vUrng);
    std::cout << "After shuffle and before sort:" << std::endl;
    std::cout << "vector<int>[0, " << PRINT_MAX << "): " << std::endl;
    vCnt = 0;
    while (vCnt < PRINT_MAX) {
        std::cout << vVec[vCnt] << " ";
        ++vCnt;
    }
    std::cout << std::endl;
    vStart = std::chrono::steady_clock::now();
    MergeSortSharedAux(vVec);
    vEnd = std::chrono::steady_clock::now();
    vLatency = vEnd - vStart;
    std::cout << "Time consumed by sorting vec with shared aux algorithm: "
        << vLatency.count() << "secs." << std::endl;
    std::cout << "After sort:" << std::endl;
    std::cout << "vector<int>[0, " << PRINT_MAX << "): " << std::endl;
    vVal = 0;
    vCnt = 0;
    for (auto i : vVec) {
        if (vCnt < PRINT_MAX) {
            std::cout << vVec[vCnt] << " ";
            ++vCnt;
        }
        EXPECT_EQ(vVal, i);
        ++vVal;
    }
    std::cout << std::endl;

    std::cout << std::endl;
    std::shuffle(vVec.begin(), vVec.end(), vUrng);
    ListNode<int> *vpList = new ListNode(vVec[0]);
    for (int i = 1; i < CONTAINER_CAPACITY; ++i) {
        vpList->Prepend(new ListNode(vVec[i]));
    }
    std::cout << "After initialization:" << std::endl;
    std::cout << "list<int>[0, " << PRINT_MAX << "): " << std::endl;
    vCnt = 0;
    ListNode<int> *vpNode = vpList;
    while (vCnt < CONTAINER_CAPACITY) {
        if (vCnt < PRINT_MAX) {
            std::cout << vpNode->mData << " ";
        }
        EXPECT_EQ(vVec[vCnt], vpNode->mData);
        ++vCnt;
        vpNode = vpNode->mpNext;
    }
    EXPECT_EQ(vpNode, vpList);
    std::cout << std::endl;
    vStart = std::chrono::steady_clock::now();
    MergeSortList(vpList);
    vEnd = std::chrono::steady_clock::now();
    vLatency = vEnd - vStart;
    std::cout << "Time consumed by sorting list with MergeSortList: "
        << vLatency.count() << "secs." << std::endl;
    std::cout << "After sort:" << std::endl;
    std::cout << "list<int>[0, " << PRINT_MAX << "): " << std::endl;
    vVal = 0;
    vCnt = 0;
    vpNode = vpList;
    while (vCnt < CONTAINER_CAPACITY) {
        if (vCnt < PRINT_MAX) {
            std::cout << vpNode->mData << " ";
        }
        EXPECT_EQ(vVal, vpNode->mData);
        ++vCnt;
        ++vVal;
        vpNode = vpNode->mpNext;
    }
    std::cout << std::endl;
    EXPECT_EQ(CONTAINER_CAPACITY, vCnt);
    while (vCnt > 0) {
        vpNode = vpList;
        vpList = vpNode->mpNext;
        vpNode->Detach();
        delete vpNode;
        --vCnt;
    }
}
