#include <cstdint>
#include <iostream>
#include <ios>

#include <gtest/gtest.h>


template<typename ObjectType>
using ObjectPrinter = void(*)(ObjectType);

void PrintUint64(uint64_t num)
{
    std::cout << std::hex << num << std::endl;
}

TEST(TemplateUsage, Alias)
{
    ObjectPrinter<uint64_t>  printer =  PrintUint64;
    
    printer(128923);
}
