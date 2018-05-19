#ifndef TEST_ENGINE_H
#define TEST_ENGINE_H


#include <string>
#include <chrono>


class TestCase
{
private:
    std::string mName;
    std::chrono::seconds mTimeout;
public:
    TestCase(std::string & const inName, std::chrono::seconds inTimeout)
        : mName {inName}, mTimeout {inTimeout}
    {}

    TestCase(std::string && inName, std::chrono::seconds inTimeout)
        : mName {inName}, mTimeout {inTimeout}
    {}

    std::string & const GetName() const { return mName; }

    std::chrono::seconds GetTimeout() const { return mTimeout; }

    virtual bool Run();
};


class TestEngine
{
};


#endif //TEST_ENGINE_H
