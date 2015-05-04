#ifndef INCLUDED_DATETIMETZ_H
#define INCLUDED_DATETIMETZ_H

#include <ostream>
#include "typetraits.h"
#include "datetime.h"

class DatetimeTz {
    Datetime d_datetime;
    int      d_timezone;
public:
    DatetimeTz()
        : d_datetime(1970, 1, 1),
          d_timezone(0)
    {}
    DatetimeTz(int year, int month, int day)
        : d_datetime(year, month, day),
          d_timezone(0)
    {}
    int year() const {
        return d_datetime.year();
    }
    int month() const {
        return d_datetime.month();
    }
    int day() const {
        return d_datetime.day();
    }
    int timezone() const {
        return d_timezone;
    }
};

inline
std::ostream& operator <<  (std::ostream& stream, DatetimeTz value) {
    return stream << "["<< value.year() << "-"
                        << value.month() << "-"
                        << value.day() << "@"
                        << value.timezone() << "]";
}

template<>
struct IsPrimitive<DatetimeTz> : TrueType {};

#endif
