#include <assert.h>
#include <iostream>
#include <vector>

//#define GTEST_DISABLED

using namespace std;

class DummyClass
{
    //using namespace std;

public:
    void RunTest()
    {

        cout << "Begin of usage test of 'class X {using namespace std; ...};'";
        cout << endl;

        vector<int> vVec = {0, 1, 2, 3};
        for (int i = 0; i < vVec.size(); ++i)
        {
#ifdef GTEST_DISABLED
            assert(vVec[i] == i);
#else
            EXPECT_EQ(vVec[i], i);
#endif
        }

        cout << "You couldn't use 'using namespace std;' in class." << endl;
        cout << "End of usage test of 'class X {using namespace std; ...};'";
        cout << endl;
    }
};

#ifdef GTEST_DISABLED
int main(void)
#else
TEST(CppUsage, UsingInFunction)
#endif
{
    DummyClass vObj;
    vObj.RunTest();
#ifdef GTEST_DISABLED
    return 0;
#endif
}
