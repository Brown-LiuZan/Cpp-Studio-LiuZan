#include <iostream>
#include <utility> //pair<T1, T2>
#include <tuple> //tuple<Ts...>
#include <gtest/gtest.h>

#include "common.h"


using namespace std;
using namespace StdCxxUsage;


TEST(TupleUsage, Constructors)
{
    cout << "Begin of test of default constructor of pair<>" << endl;
    pair<Person, int> vNullRecord;
    EXPECT_EQ(vNullRecord.second, 0);
    auto vNobody = vNullRecord.first;
    EXPECT_TRUE(vNobody.GetName().empty());    
    EXPECT_EQ(vNobody.GetBirthday().GetYear(), 0);
    EXPECT_EQ(vNobody.GetBirthday().GetMonth(), 0);
    EXPECT_EQ(vNobody.GetBirthday().GetDay(), 0);
    EXPECT_FALSE(vNobody.IsMale());
    cout << "End of test of default constructor of pair<>" << endl;
}
