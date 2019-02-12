#ifndef LIUZAN_CXX_USAGE_COMMON_H
#define LIUZAN_CXX_USAGE_COMMON_H


#include<string>
#include<cstdint>


namespace liuzan {
namespace cxxusage {

class Person
{
public:
    enum Gender
    {
        kMale,
        kFemale
    };

    struct Birthday
    {
        int mYear:16;
        int mMonth:8;
        int mDayInMonth:8;

        Birthday(int inYear, int inMonth, int inDayInMonth):
            mYear(inYear), mMonth(inMonth), mDayInMonth(inDayInMonth)
        {
            if (inYear < 0 ||
                inMonth < 1 || inMonth > 12 ||
                inDayInMonth < 1 || inDayInMonth > 31)
                throw std::invalid_argument("Invalid birthday format");
        }
    };

private:
    std::string mName;
    Gender mGender;
    Birthday mBirthday;
};

}  // namespace cxxusage
}  // namespace liuzan
#endif
