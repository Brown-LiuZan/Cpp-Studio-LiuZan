#include <iostream>
#include <string>


using namespace std;

void CCUTestRawString()
{
    cout << "===>Begin of raw string test<===" << endl;
    string vRawStr1 {R"(\\n)"};
    string vRawStr2 {R"d(Hi
        world!
Do you love C++?
    )")d"};

    cout << vRawStr1 << endl;
    cout << vRawStr2 << endl;
    cout << "===>End of raw string test<===" << endl;
    cout << endl;
}
