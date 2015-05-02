#ifndef NULLABLE_H
#define NULLABLE_H

#include"typetraits.h"
#include"objectbuffer.h"

template<typename T>
class Nullable {
    bool            d_isNull;
    ObjectBuffer<T> d_value;
public:
    Nullable() : d_isNull(true){
    }

    Nullable(const T& other)
        : d_isNull(true)
    {
        reset(other);
    }

    void reset() {
        d_value.reset();
        d_isNull = false;
    }

    void reset(const T& value) {
        d_value.reset(value);
        d_isNull = false;
    }

    void setNull() {
        d_value.setNull();
        d_isNull = true;
    }

    bool isNull() const {
        return d_isNull;
    }

    const T& value() const {
        return d_value.value();
    }
};

template<typename T>
struct IsNullable<Nullable<T> > : TrueType {};

#endif // NULLABLE_H
