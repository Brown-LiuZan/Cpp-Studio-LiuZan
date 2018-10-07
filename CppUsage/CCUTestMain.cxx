#include <iostream>
#include "CCUTest.h"


using namespace std;


//int main(int inArgc, char ** inpArgv, char ** inpEnv)
int main()
{
    cout << "Hello, world!" << endl;

#if (CCU_TEST_UTILITY == 1)
    CCUTestRawString();
#endif

#if (CCU_TEST_UTILITY == 1)
    CCUTestUtility();
#endif

    return 0;
}
