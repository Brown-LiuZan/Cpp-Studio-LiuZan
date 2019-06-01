#include <gtest/gtest.h>

struct InnerGDCDemo {
    int inGDCFirst;
    int inGDCSecond;
};

struct InnerMDPCDemo {
    int inMDPCFirst;
    int inMDPCSecond;

    InnerMDPCDemo():
        inMDPCSecond(22)
    {}
};

struct GccDefaultCtorDemo:
    public InnerGDCDemo,
    public InnerMDPCDemo
{
    int first;
    int second;
};

struct MyDefaultPartialCtorDemo:
    public InnerGDCDemo,
    public InnerMDPCDemo
{
    int first;
    int second;

    MyDefaultPartialCtorDemo():
        second(2)
    {}
};

struct MyDefaultFullCtorDemo:
    public InnerGDCDemo,
    public InnerMDPCDemo
{
    int first;
    int second;

    MyDefaultFullCtorDemo():
        InnerGDCDemo(),
        InnerMDPCDemo(),
        first(1),
        second(2)
    {}
};

 
TEST(Initialization, ValueInitialization)
{
    static GccDefaultCtorDemo sGDCDemo{};
    static MyDefaultPartialCtorDemo sMDPCDemo{};
    static MyDefaultFullCtorDemo sMDFCDemo{};
    GccDefaultCtorDemo vGDCDemo{};
    MyDefaultPartialCtorDemo vMDPCDemo{};
    MyDefaultFullCtorDemo vMDFCDemo{};

    EXPECT_EQ(0, sGDCDemo.first);
    EXPECT_EQ(0, sGDCDemo.second);
    EXPECT_EQ(0, sGDCDemo.inGDCFirst);
    EXPECT_EQ(0, sGDCDemo.inGDCSecond);
    EXPECT_EQ(0, sGDCDemo.inMDPCFirst);
    EXPECT_EQ(22, sGDCDemo.inMDPCSecond);

    EXPECT_EQ(0, sMDPCDemo.first);
    EXPECT_EQ(2, sMDPCDemo.second);
    EXPECT_EQ(0, sGDCDemo.inGDCFirst);
    EXPECT_EQ(0, sGDCDemo.inGDCSecond);
    EXPECT_EQ(0, sGDCDemo.inMDPCFirst);
    EXPECT_EQ(22, sGDCDemo.inMDPCSecond);

    EXPECT_EQ(1, sMDFCDemo.first);
    EXPECT_EQ(2, sMDFCDemo.second);
    EXPECT_EQ(0, sGDCDemo.inGDCFirst);
    EXPECT_EQ(0, sGDCDemo.inGDCSecond);
    EXPECT_EQ(0, sGDCDemo.inMDPCFirst);
    EXPECT_EQ(22, sGDCDemo.inMDPCSecond);

    EXPECT_EQ(0, vGDCDemo.first);
    EXPECT_EQ(0, vGDCDemo.second);
    EXPECT_EQ(0, vGDCDemo.inGDCFirst);
    EXPECT_EQ(0, vGDCDemo.inGDCSecond);
    EXPECT_EQ(0, vGDCDemo.inMDPCFirst);
    EXPECT_EQ(22, vGDCDemo.inMDPCSecond);

//    EXPECT_NE(0, vMDPCDemo.first);
    EXPECT_EQ(2, vMDPCDemo.second);
//    EXPECT_NE(0, vMDPCDemo.inGDCFirst);
//    EXPECT_NE(0, vMDPCDemo.inGDCSecond);
//    EXPECT_NE(0, vMDPCDemo.inMDPCFirst);
    EXPECT_EQ(22, vMDPCDemo.inMDPCSecond);

    EXPECT_EQ(1, vMDFCDemo.first);
    EXPECT_EQ(2, vMDFCDemo.second);
    EXPECT_EQ(0, vMDFCDemo.inGDCFirst);
    EXPECT_EQ(0, vMDFCDemo.inGDCSecond);
//    EXPECT_NE(0, vMDFCDemo.inMDPCFirst);
    EXPECT_EQ(22, vMDFCDemo.inMDPCSecond);
 }

TEST(Initialization, DefaultInitialization)
{
    static GccDefaultCtorDemo sGDCDemo;
    static MyDefaultPartialCtorDemo sMDPCDemo;
    static MyDefaultFullCtorDemo sMDFCDemo;
    GccDefaultCtorDemo vGDCDemo;
    MyDefaultPartialCtorDemo vMDPCDemo;
    MyDefaultFullCtorDemo vMDFCDemo;

    EXPECT_EQ(0, sGDCDemo.first);
    EXPECT_EQ(0, sGDCDemo.second);
    EXPECT_EQ(0, sGDCDemo.inGDCFirst);
    EXPECT_EQ(0, sGDCDemo.inGDCSecond);
    EXPECT_EQ(0, sGDCDemo.inMDPCFirst);
    EXPECT_EQ(22, sGDCDemo.inMDPCSecond);

    EXPECT_EQ(0, sMDPCDemo.first);
    EXPECT_EQ(2, sMDPCDemo.second);
    EXPECT_EQ(0, sGDCDemo.inGDCFirst);
    EXPECT_EQ(0, sGDCDemo.inGDCSecond);
    EXPECT_EQ(0, sGDCDemo.inMDPCFirst);
    EXPECT_EQ(22, sGDCDemo.inMDPCSecond);

    EXPECT_EQ(1, sMDFCDemo.first);
    EXPECT_EQ(2, sMDFCDemo.second);
    EXPECT_EQ(0, sGDCDemo.inGDCFirst);
    EXPECT_EQ(0, sGDCDemo.inGDCSecond);
    EXPECT_EQ(0, sGDCDemo.inMDPCFirst);
    EXPECT_EQ(22, sGDCDemo.inMDPCSecond);

//    EXPECT_NE(0, vGDCDemo.first);
//    EXPECT_NE(0, vGDCDemo.second);
//    EXPECT_NE(0, vGDCDemo.inGDCFirst);
//    EXPECT_NE(0, vGDCDemo.inGDCSecond);
//    EXPECT_NE(0, vGDCDemo.inMDPCFirst);
    EXPECT_EQ(22, vGDCDemo.inMDPCSecond);

//    EXPECT_NE(0, vMDPCDemo.first);
    EXPECT_EQ(2, vMDPCDemo.second);
//    EXPECT_NE(0, vMDPCDemo.inGDCFirst);
//    EXPECT_NE(0, vMDPCDemo.inGDCSecond);
//    EXPECT_NE(0, vMDPCDemo.inMDPCFirst);
    EXPECT_EQ(22, vMDPCDemo.inMDPCSecond);

    EXPECT_EQ(1, vMDFCDemo.first);
    EXPECT_EQ(2, vMDFCDemo.second);
//    EXPECT_NE(0, vMDFCDemo.inGDCFirst);
//    EXPECT_NE(0, vMDFCDemo.inGDCSecond);
//    EXPECT_NE(0, vMDFCDemo.inMDPCFirst);
    EXPECT_EQ(22, vMDFCDemo.inMDPCSecond);
 }
