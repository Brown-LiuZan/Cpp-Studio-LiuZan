#ifndef LZ_INTERFACE_SORTER_H
#define LZ_INTERFACE_SORTER_H

#include <vector>
#include <list>

namespace LiuZan
{
    class Sorter
    {
    public:
        template<typename ElemType>
        virtual void Sort(std::vector<ElemType> & ioVec) = 0;

        template<typename ElemType>
        virtual void Sort(std::list<ElemType> & ioList) = 0;
    };
}

#endif //LZ_INTERFACE_SORTER_H
