#include <iostream>
#include <utility>
#include <string>
#include <cstdint>

using namespace std;

void TestPair(void)
{
    pair<string, uint64_t> vHashEntry;
    cout << "Default pair<string, uint64_t>: ("
         << get<0>(vHashEntry) << ','
         << get<1>(vHashEntry) << ')'
         << endl;

    vHashEntry.first = string("Pair"); 
    vHashEntry.second = 0xFEDCBA9876543210;
    cout << "pair<Pair, 0xFEDCBA9876543210>: ("
         << get<0>(vHashEntry) << ','
         << hex << get<1>(vHashEntry) << "H)"
         << endl;
}

void CCUTestUtility(void)
{
    cout << "===>Begin of utility library usage test<===" << endl;

    TestPair();

    cout << "===>End of utility library usage test<===" << endl;
    cout << endl;
}
