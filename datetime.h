#ifndef INCLUDED_DATETIME_H
#define INCLUDED_DATETIME_H

#include <ostream>
#include "typetraits.h"

class Datetime {
    int d_year;
    int d_month;
    int d_day;
public:
    Datetime()
        :d_year(1970), d_month(1), d_day(1)
    {}
    Datetime(int year, int month, int day)
        :d_year(year), d_month(month), d_day(day)
    {}

    int year() const {
        return d_year;
    }

    int month() const {
        return d_month;
    }

    int day() const {
        return d_day;
    }
};

inline
std::ostream& operator <<  (std::ostream& stream, Datetime value) {
    return stream << "[" << value.year() << "-"
                         << value.month() << "-"
                         << value.day() << "]";
}

template<>
struct IsPrimitive<Datetime> : TrueType {};

#endif
