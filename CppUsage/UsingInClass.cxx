//#define GTEST_DISABLED
#ifdef GTEST_DISABLED
#include <assert.h>
#else
#include <gtest/gtest.h>
#endif //GTEST_DISABLED
#include <iostream>
#include <vector>


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
        for (unsigned i = 0; i < vVec.size(); ++i)
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
TEST(CppUsage, UsingInClass)
#endif
{
    DummyClass vObj;
    vObj.RunTest();
#ifdef GTEST_DISABLED
    return 0;
#endif
}
