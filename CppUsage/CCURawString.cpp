#include <iostream>
#include <string>


using namespace std;

void CCUTestRawString()
{
    string vRawStr1 {R"(\\n)"};
    string vRawStr2 {R"d(Hi
        world!
Do you love C++?
    )")d"};

    cout << vRawStr1 << endl;
    cout << vRawStr2 << endl;
}
