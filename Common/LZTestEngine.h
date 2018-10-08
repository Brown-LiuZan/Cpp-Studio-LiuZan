#ifndef TEST_ENGINE_H
#define TEST_ENGINE_H


#include <string> //std::string
#include <chrono> //std::chrono::milliseconds
#include <deque> //std::deque
#include <memory> //std::unique_ptr
#include <thread> //std::thread


class TestCase
{
private:
    std::string mName;
    std::chrono::milliseconds mTimeout;

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
private:
    std::deque<std::unique_ptr<TestCase>> mStream;
public:
    void EnqueueCase(std::unique_ptr<TestCase> inNewCase)
    {
        mStream.push_back(inNewCase);
    }

    std::unique_ptr<TestCase> DequeueCase()
    {
        std::unique_ptr<TestCase> vHeadCase = mStream.front();
        mStream.pop_front();
        return vHeadCase;
    }
};

class TestEngine
{
};


#endif //TEST_ENGINE_H
