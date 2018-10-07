#ifndef LZ_MERGE_SORT_H
#define LZ_MERGE_SORT_H

#include <vector>
#include <list>

namespace LiuZan
{
    template<typename ElemType>
    void MergeSort(std::vector<ElemType> & ioVec)
    {
        //Stopping conditions
        if (ioVec.size() < 2) return;

        //Auxilary vector.
        std::vector<ElemType> vAuxVec(ioVec.size());

        //Lambda to merge two sorted partitions.
        auto MergeSortedParts = [](std::vector<ElemType> & vDest, std::vector<ElemType> const & vSrc,
                                   size_t vSrcStart, size_t vSrcSizeA, size_t vSrcSizeB)
        {
            size_t vDestIndex = vSrcStart;
            size_t vFirstIndex = vSrcStart, vFirstEnd = vFirstIndex + vSrcSizeA;
            size_t vSecondIndex = vFirstEnd, vSecondEnd = vSecondIndex + vSrcSizeB;
            while (vFirstIndex < vFirstEnd || vSecondIndex < vSecondEnd)
            {
                if (vFirstIndex >= vFirstEnd)
                {
                    vDest[vDestIndex++] = vSrc[vSecondIndex++];
                }
                else if (vSecondIndex >= vSecondEnd)
                {
                    vDest[vDestIndex++] = vSrc[vFirstIndex++];
                }
                else
                {
                    if (vSrc[vFirstIndex] <= vSrc[vSecondIndex]) vDest[vDestIndex++] = vSrc[vFirstIndex++];
                    else vDest[vDestIndex++] = vSrc[vSecondIndex++];
                }
            }
        }

        //Iteratively merging
        size_t vMergedWinSize = 2;
        bool vMergeToAux = true;
        while (vMergedWinSize <= ioVec.size())
        {
            size_t const MAX_FULL_WINDOWS = ioVec.size() / vMergedWinSize;
            size_t const SORTED_PARTITION_SIZE = vMergedWinSize / 2;

            std::vector<ElemType> & vSrc = vMergeToAux ? ioVec : vAuxVec;
            std::vector<ElemType> & vDest = vMergeToAux ? vAuxVec : ioVec;

            size_t vSrcStart = 0;
            for (size_t vWinIndex = 0; vWinIndex < MAX_FULL_WINDOWS; ++vWinIndex)
            {
                MergeSortedParts(vDest, vSrc, vSrcStart, SORTED_PARTITION_SIZE, SORTED_PARTITION_SIZE);
                vSrcStart += vMergedWinSize;
            }
            
            //Handling the tailing non-full merged window.
            size_t vNonfullWindowSize = ioVec.size() - vSrcStart;
            if (vNonfullWindowSize > SORTED_PARTITION_SIZE)
            {
                MergeSortedParts(vDest, vSrc, vSrcStart, SORTED_PARTITION_SIZE,
                                 vNonfullWindowSize - SORTED_PARTITION_SIZE);
            }

            vMergeToAux = !vMergeToAux;
            vMergedWinSize *= 2;
        }

        //Final asymmetric merging
        vMergedWinSize /= 2;
        if (vMergedWinSize < ioVec.size())
        {
            std::vector<ElemType> & vSrc = vMergeToAux ? ioVec : vAuxVec;
            std::vector<ElemType> & vDest = vMergeToAux ? vAuxVec : ioVec;

            MergeSortedParts(vDest, vSrc, 0, vMergedWinSize, ioVec.size() - vMergedWinSize);
        }

        //Make sure the final result resides in user's vector.
        if (vMergeToAux)
        {
            swap(ioVec, vAuxVec);
        }
    }
}

#endif //LZ_MERGE_SORT_H
