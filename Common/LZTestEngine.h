#ifndef TEST_ENGINE_H
#define TEST_ENGINE_H


#include <string>
#include <chrono>
#include <queue>
#include <memory>
#include <thread>


class TestCase
{
private:
    std::string mName;
    std::chrono::seconds mTimeout;

public:
    explicit TestCase(std::string const & inName)
        : mName(inName), mTimeout()
    {}

    explicit TestCase(char const * inName)
        : mName(inName), mTimeout()
    {}

    std::string const & GetName() const { return mName; }

    void SetTimeout(std::chrono::seconds inSecs) { mTimeout = inSecs; }
    std::chrono::seconds GetTimeout() const { return mTimeout; }

    virtual bool Run() = 0;
};

class LZTestStream
{
};

class TestEngine
{
};


#endif //TEST_ENGINE_H
