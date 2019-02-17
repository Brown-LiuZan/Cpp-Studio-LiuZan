#ifndef LIUZAN_COMMON_TUPLE_PRINTER_H
#define LIUZAN_COMMON_TUPLE_PRINTER_H


#include "cxx_version_macroes.h"

#include <tuple>
#include <iostream>

namespace liuzan {
namespace common {

#if __cplusplus >= CPLUSPLUS_VAL_FOR_11
template<int IDX, int MAX, typename... Types>
struct TUPLE_PRINTER {
    static void print(std::ostream& outStream,
            const std::tuple<Types...>& inTuple)
    {
        outStream << std::get<IDX>(inTuple);
        outStream << (IDX + 1 == MAX ? "" : ",");
        TUPLE_PRINTER<IDX+1, MAX, Types...>::print(outStream, inTuple);
    }
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
template<int MAX, typename... Types>
struct TUPLE_PRINTER<MAX, MAX, Types...> {
    static void print(std::ostream& outStream,
            const std::tuple<Types...>& inTuple)
    {}
};
#pragma GCC diagnostic pop

template<typename... Types>
void print_tuple(std::ostream& outStream, const std::tuple<Types...> inTuple)
{
    TUPLE_PRINTER<0, sizeof...(Types), Types...>::print(outStream, inTuple);
}
#endif

} // namespace common
} // namespace liuzan


#endif // LIUZAN_COMMON_TUPLE_PRINTER_H
