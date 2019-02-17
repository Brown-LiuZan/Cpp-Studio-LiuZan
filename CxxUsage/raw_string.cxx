#include <iostream>
#include <string>

#include "common.h"

using namespace std;

void CCUTestRawString()
{
    cout << "===>Begin of raw string test<===" << endl;
#if __cplusplus >= CPLUSPLUS_VAL_FOR_11
    string vRawStr1 {R"(\\n)"};
    string vRawStr2 {R"d(Hi
        world!
Do you love C++?
    )")d"};

    cout << vRawStr1 << endl;
    cout << vRawStr2 << endl;
#else
    cout << "No raw string support before C++11." << endl;
#endif
    cout << "===>End of raw string test<===" << endl;
    cout << endl;
}
