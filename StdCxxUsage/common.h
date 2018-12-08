#ifndef CPPSTUDIO_STDCXXUSAGE_COMMON_H_
#define CPPSTUDIO_STDCXXUSAGE_COMMON_H_


#include <string>


namespace StdCxxUsage {


struct Birthday {
    int mYear;
    int mMonth;
    int mDay;
    Birthday(int year, int month, int day):
        mYear(year),
        mMonth(month),
        mDay(day)
    {}
    int GetYear() const
    {
        return mYear;
    }
    int GetMonth() const
    {
        return mMonth;
    }
    int GetDay() const
    {
        return mDay;
    }
    void SetYear(int year)
    {
        mYear = year;
    }
    void SetMonth(int month)
    {
        mMonth = month;
    }
    void SetDay(int day)
    {
        mDay = day;
    }
};

class Person {
public:
    Person():
        mName(),
        mBirthday(0, 0, 0),
        mIsMale(false)
    {}
    Person(std::string const & name, Birthday const & birthday, bool male):
        mName(name),
        mBirthday(birthday),
        mIsMale(male)
    {}
    Person(std::string const & name, int year, int month, int day, bool male):
        mName(name),
        mBirthday(year, month, day),
        mIsMale(male)
    {}
    std::string const & GetName() const
    {
        return mName;
    }
    Birthday const & GetBirthday() const
    {
        return mBirthday;
    }
    bool IsMale() const
    {
        return mIsMale;
    }

private:
    std::string mName;
    Birthday mBirthday;
    bool mIsMale;
};


} // namespace StdCxxUsage


#endif // CPPSTUDIO_STDCXXUSAGE_COMMON_H_
