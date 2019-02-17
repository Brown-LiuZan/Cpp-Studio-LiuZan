#include <iostream>
#include <utility> //pair<T1, T2>
#include <tuple> //tuple<Ts...>
#include <gtest/gtest.h>

#include "Common/birthday_person_geolocation.h"
#include "Common/cxx_version_macroes.h"
#include "Common/tuple_printer.h"


using std::cout;
using std::endl;
using std::piecewise_construct;
using std::forward_as_tuple;
using std::pair;
using std::get;
using std::make_tuple;
using liuzan::common::Birthday;
using liuzan::common::Person;
using liuzan::common::GeoLocation;
using liuzan::common::print_tuple;


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

    pair<Birthday, GeoLocation> vBG(
            piecewise_construct,
            forward_as_tuple(1983, 9, 8),
            forward_as_tuple(101.3, 40.5, 1500.0));
    EXPECT_EQ(vBG.first, Birthday(1983, 9, 8));
    cout << get<0>(vBG) << endl;
    EXPECT_EQ(vBG.second, GeoLocation(101.3, 40.5, 1500.0));
    cout << get<1>(vBG) << endl;

    cout << "print_tuple(): (";
    print_tuple(cout, make_tuple("liuzan", "male", 1983));
    cout << ")" << endl;
}
