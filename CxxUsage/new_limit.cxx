#include <gtest/gtest.h>

#include <iostream>
#include <iomanip>

void NewObjectInfinitely()
{
    double vDb = 1.2345;
    uint64_t vCnt = 1;
    while (true)
    {
        try {
            double * vp = new double[1024 * 1024];
            vp[0] = vDb * vCnt;
            std::cout << vCnt << ": ";
            std::cout << std::setprecision(12) << vp[0] << std::endl;
            ++vCnt;
        } catch (...) {
            std::cerr << "New failure." << std::endl;
        }
    }
}

TEST(TSCxxUsage, TCNewObjInf)
{
    NewObjectInfinitely();
}
