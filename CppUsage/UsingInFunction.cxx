//#define GTEST_DISABLED
#ifdef GTEST_DISABLED
#include <assert.h>
#else
#include <gtest/gtest.h>
#endif // GTEST_DISABLED
#include <iostream>
#include <vector>


static void RunTest()
{
    using namespace std;

    cout << "Begin of usage test of 'void func() {using namespace std; ...}'";
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

    cout << "You could use 'using namespace std;' in function." << endl;
    cout << "End of usage test of 'void func() {using namespace std; ...}'";
    cout << endl;
}

#ifdef GTEST_DISABLED
int main(void)
#else
TEST(CppUsage, UsingInFunction)
#endif
{
    RunTest();
#ifdef GTEST_DISABLED
    return 0;
#endif
}
