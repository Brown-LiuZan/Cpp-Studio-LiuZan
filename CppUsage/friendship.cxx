#include <iostream>
#include <gtest/gtest.h>


class MyGlobalFriendClass;
class NonExistedClass;

namespace LiuZan
{
    class Me
    {
        //A cross-namespace-boundary friend declaration needs
        //a fully qualified name.
        friend class ::MyGlobalFriendClass;
        friend class ::NonExistedClass;

        void SayHi()
        {
            std::cout << "Hi!" << std::endl;
        }
    };
}

class MyGlobalFriendClass
{
public:
    void Test()
    {
        LiuZan::Me vMe;
        vMe.SayHi();
    }
};

TEST(CppUsage, Friendship)
{
    MyGlobalFriendClass vObj;
    vObj.Test();
}

