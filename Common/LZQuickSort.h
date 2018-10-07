#ifndef LZ_QUICK_SORT_H
#define LZ_QUICK_SORT_H

#include <vector> //std::vector
#include <utility> //std::swap()
#include "LZAssert" //LiuZan::DynamicAssert()

namespace LiuZan
{
    /*
     * Quick sort is better to be called partition sort.
     * It's suitable to sort an array-like set of same-type elements.
     * To use it with non-arithmatic type, you should overload >= operator with your expected semantics.
     * */
    template<typename ElemType>
    void QuickSort(std::vector<ElemType> & ioVec, size_t inStart, size_t inEnd)
    {
        DynamicAssert(inStart <= inEnd && ioVec.size() >= inEnd,
            "[inStart, inEnd) must be a valid range of ioVec.");

        // Stopping condition
        if (inStart + 1 >= inEnd) return;

        // Choose the middle one as partitioning element to avoid stack depth nightmare.
        size_t vMid = (inStart + inEnd) / 2;
        swap(ioVec[inStart], ioVec[vMid]);

        // Partition by scanning and swapping exchangable pair.
        size_t vForward = inStart;
        size_t vBackward = inEnd;
        while (vForward < vBackward)
        {
            while (ioVec[++vForward] <= ioVec[inStart] && vForward < vBackward);
            while (ioVec[--vBackward] >= ioVec[inStart] && vBackward > vForward);
            if (vBackward < vForward) swap(ioVec[vForward], ioVec[vBackward]);
        }

        // Recursively partitioning.
        swap(ioVec[inStart], ioVec[vBackward]);
        QuickSort(ioVec, inStart, vBackward);
        QuickSort(ioVec, vForward, inEnd); 
    }
}

#endif //LZ_QUICK_SORT_H
