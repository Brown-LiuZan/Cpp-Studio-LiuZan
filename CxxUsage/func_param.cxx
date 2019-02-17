#include <iostream>

#include "Common/cxx_version_macroes.h"
#include "Common/birthday_person_geolocation.h"

#if __cplusplus >= CPLUSPLUS_VAL_FOR_11
#include <gtest/gtest.h>
#endif

using namespace std;
using namespace liuzan::common;

static void PrintBirthday(const Birthday& obj)
{
    cout << obj << endl;
}

#if __cplusplus >= CPLUSPLUS_VAL_FOR_11
TEST(CxxUsageTest, FuncConstRefParamTest)
#else
void FuncConstRefParamTest()
#endif
{
    Birthday vBirth;
    PrintBirthday(vBirth);
    PrintBirthday(Birthday(1983, 9, 8));
}
