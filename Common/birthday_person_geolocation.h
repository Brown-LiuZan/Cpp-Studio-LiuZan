#ifndef CPPSTUDIO_STDCXXUSAGE_COMMON_H_
#define CPPSTUDIO_STDCXXUSAGE_COMMON_H_


#include <string>
#include <ostream>
#include <cmath>

#include "cxx_version_macroes.h"


namespace liuzan {
namespace common {

struct Birthday {
    Birthday(int year, int month, int day):
        mYear(year),
        mMonth(month),
        mDay(day)
    {}

#if __cplusplus >= CPLUSPLUS_VAL_FOR_11
    Birthday(): Birthday(0, 0, 0)
    {}
#else
    Birthday():
        mYear(0),
        mMonth(0),
        mDay(0)
    {}
#endif

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

    int mYear;
    int mMonth;
    int mDay;
};

inline std::ostream & operator << (std::ostream & os, const Birthday& birth)
{
    os << birth.GetYear() << "-";
    os << birth.GetMonth() << "-";
    os << birth.GetDay();

    return os;
}

inline bool operator ==(const Birthday& a, const Birthday& b)
{
    return a.GetYear() == b.GetYear() &&
        a.GetMonth() == b.GetMonth() &&
        a.GetDay() == b.GetDay();
}

inline bool operator !=(const Birthday& a, const Birthday& b)
{
    return !(a == b);
}

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

inline std::ostream& operator << (std::ostream& os, const Person& person)
{
    os << person.GetName() << ",";
    os << person.GetBirthday() << ",";
    os << (person.IsMale() ? "Male" : "Female");

    return os;
}

inline bool operator ==(const Person& a, const Person& b)
{
    return a.GetName() == b.GetName() &&
        a.GetBirthday() == b.GetBirthday() &&
        a.IsMale() == b.IsMale();
}

inline bool operator !=(const Person& a, const Person& b)
{
    return !(a == b);
}

class GeoLocation {
public:
    GeoLocation(float longitude, float latitude, float altitude):
        mLongitude(longitude),
        mLatitude(latitude),
        mAltitude(altitude)
    {}

#if __cplusplus >= CPLUSPLUS_VAL_FOR_11
    GeoLocation():
        GeoLocation(0.0f, 0.0f, 0.0f)
    {}
#else
    GeoLocation():
        mLongitude(0.0f),
        mLatitude(0.0f),
        mAltitude(0.0f)
    {}
#endif

    float GetLongitude() const
    {
        return mLongitude;
    }

    float GetLatitude() const
    {
        return mLatitude;
    }

    float GetAltitude() const
    {
        return mAltitude;
    }

    void SetLongitude(float longitude)
    {
        mLongitude = longitude;
    }

    void SetLatitude(float latitude)
    {
        mLatitude = latitude;
    }

    void SetAltitude(float altitude)
    {
        mAltitude = altitude;
    }

private:
    float mLongitude;
    float mLatitude;
    float mAltitude;
};

inline std::ostream& operator <<(std::ostream& os, const GeoLocation& loc)
{
    os << loc.GetLongitude() << "°,";
    os << loc.GetLatitude() << "°,";
    os << loc.GetAltitude() << "m";

    return os;
}

inline bool operator ==(const GeoLocation& a, const GeoLocation& b)
{
    return std::fabs(a.GetLongitude() - b.GetLongitude()) < 0.0001 &&
    std::fabs(a.GetLatitude() - b.GetLatitude()) < 0.0001 &&
    std::fabs(a.GetAltitude() - b.GetAltitude()) < 1.0;
}

inline bool operator !=(const GeoLocation& a, const GeoLocation& b)
{
    return !(a != b);
}

} // namespace common
} // namespace liuzan


#endif // CPPSTUDIO_STDCXXUSAGE_COMMON_H_
