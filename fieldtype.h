#ifndef FIELDTYPE_H
#define FIELDTYPE_H

#include "typetraits.h"

class FieldType {
public:
    enum Value {
        TYPE_NULL = 0,
        TYPE_BOOL,

        TYPE_CHAR,
        TYPE_SIGNED_CHAR,
        TYPE_UNSIGNED_CHAR,

        TYPE_SIGNED_SHORT,
        TYPE_UNSIGNED_SHORT,

        TYPE_SIGNED_INTEGER,
        TYPE_UNSIGNED_INTEGER,

        TYPE_SIGNED_LONG,
        TYPE_UNSIGNED_LONG,

        TYPE_SIGNED_LONG_LONG,
        TYPE_UNSIGNED_LONG_LONG,

        TYPE_DATETIME,
        TYPE_DATETIMETZ,

        TYPE_FLOAT,
        TYPE_DOUBLE,

        TYPE_STRING
    };

    static int toInt(FieldType::Value value) {
        return value;
    }
};

template<>
struct IsEnum<FieldType::Value> : TrueType {
    typedef FieldType Wrapper;
};

#endif // FIELDTYPE_H
