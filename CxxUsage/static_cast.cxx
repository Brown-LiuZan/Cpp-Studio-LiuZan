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

    cout << "Begin of usage test of static_cast<int *>(0)" << endl;

    int a = 10;
    int* vpInteger = &a;
    try {
        vpInteger = static_cast<int*>(0);
        if (nullptr == vpInteger)
        {
            cout << "static_cast<int*>(0) return nullptr" << endl;
        }
    } catch (...) {
        cout << "static_cast<int*>(0) throws exception." << endl;
    }

    cout << "End of usage test of static_cast<int *>(0)";
    cout << endl;
}

#ifdef GTEST_DISABLED
int main(void)
#else
TEST(CppUsage, StaticCastNull)
#endif
{
    RunTest();
#ifdef GTEST_DISABLED
    return 0;
#endif
}
