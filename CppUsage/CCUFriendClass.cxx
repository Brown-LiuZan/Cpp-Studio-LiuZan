#include <iostream>


class MyGlobalFriendClass;

namespace LiuZan
{
    class Me
    {
        //A cross-namespace-boundary friend declaration needs
        //a fully qualified name.
        friend class ::MyGlobalFriendClass;

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

int main()
{
    MyGlobalFriendClass vObj;

    vObj.Test();
}

