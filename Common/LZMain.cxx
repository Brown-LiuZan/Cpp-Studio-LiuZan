#include <iostream>
#include "LZTestEngine.h"
#define DYNAMIC_ASSERT_EXCEPTION
#include "LZAssert.h"

using namespace std;
using namespace LiuZan;

/* === Test facility of LZAssert.h === */
class TCDynamicAssert : public TestCase
{
public:
    TCDynamicAssert(string const & inName)
        : TestCase(inName)
    {}

    TCDynamicAssert(char const * inName)
        : TestCase(inName)
    {}

    bool Run() override
    {
        try {
            int vCntFailed = 0;
            
            StaticAssert(sizeof(size_t) == sizeof(void *));

            DynamicAssert(sizeof(size_t) == sizeof(void *), "Both size_t and 'void *' should be same-sized."); 
            cout << "Both size_t and 'void *' are always same-sized." << endl;

            try {
                DynamicAssert(false, "Intended failure one.");
            } catch (AssertException const & ae) {
                cout << ae.what() << endl;
                ++vCntFailed;
            }

            DynamicAssert(1 == vCntFailed, "Test of assert facility failed.");
            cout << "Test of LZAssert.h passed." << endl;
            
        } catch (AssertException const & ae) {
            cerr << ae.what() << endl;
            return false;
        }

        return true;
    }
};


int main(int argc, char **argv)
{
    TCDynamicAssert vTc("Test of assert facility");

    cout << "===>Begin: " << vTc.GetName() << "<===" << endl;
    cout << (vTc.Run() ? "Succeeded" : "Failed") << endl;
    cout << "===>End: " << vTc.GetName() << "<===" << endl;
    cout << endl;

    return 0;
}
