#include <iostream>

class GlobalClass
{
public:
    void Test(void)
    {
        std::cout << "Hi, I'm from global namespace." << std::endl;
    }
};

namespace Outer
{
    class OuterClass
    {
    public:
        void Test(void)
        {
            std::cout << "Hi, I'm from outer namespace." << std::endl;
        }
    };

    namespace Inner
    {
        class InnerClass
        {
        public:
            void Test(void)
            {
                std::cout << "Hi, I'm from inner namespace." << std::endl;

#if 1
                OuterClass vOuter;
                vOuter.Test();

                GlobalClass vGlobal;
                vGlobal.Test();
#endif
            }
        };
    }
}

int main(void)
{
    Outer::Inner::InnerClass vTestObj;
    vTestObj.Test();
    return 0;
}
