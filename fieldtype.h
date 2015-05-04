#ifndef INCLUDED_FIELDTYPE_H
#define INCLUDED_FIELDTYPE_H

#include "typetraits.h"

class FieldType {
public:
    enum Value {
        TYPE_NULL = 0,
        TYPE_BOOL,

        TYPE_SIGNED_CHAR,
        TYPE_UNSIGNED_CHAR,

        TYPE_SIGNED_SHORT,
        TYPE_UNSIGNED_SHORT,

        TYPE_SIGNED_INTEGER,
        TYPE_UNSIGNED_INTEGER,

        TYPE_SIGNED_LONG_LONG,
        TYPE_UNSIGNED_LONG_LONG,

        TYPE_DATETIME,
        TYPE_DATETIMETZ,

        TYPE_FLOAT,
        TYPE_DOUBLE,

        TYPE_STRING,
        TYPE_BLOB
    };

    static int toInt(FieldType::Value value) {
        return value;
    }

    static const char *toString(FieldType::Value value) {
        switch(value) {
        case TYPE_NULL:
            return "TYPE_NULL";
        case TYPE_BOOL:
            return "TYPE_BOOL";
        case TYPE_SIGNED_CHAR:
            return "TYPE_SIGNED_CHAR";
        case TYPE_UNSIGNED_CHAR:
            return "TYPE_UNSIGNED_CHAR";
        case TYPE_SIGNED_SHORT:
            return "TYPE_SIGNED_SHORT";
        case TYPE_UNSIGNED_SHORT:
            return "TYPE_UNSIGNED_SHORT";
        case TYPE_SIGNED_INTEGER:
            return "TYPE_SIGNED_INTEGER";
        case TYPE_UNSIGNED_INTEGER:
            return "TYPE_UNSIGNED_INTEGER";
        case TYPE_SIGNED_LONG_LONG:
            return "TYPE_SIGNED_LONG_LONG";
        case TYPE_UNSIGNED_LONG_LONG:
            return "TYPE_UNSIGNED_LONG_LONG";
        case TYPE_DATETIME:
            return "TYPE_DATETIME";
        case TYPE_DATETIMETZ:
            return "TYPE_DATETIMETZ";
        case TYPE_FLOAT:
            return "TYPE_FLOAT";
        case TYPE_DOUBLE:
            return "TYPE_DOUBLE";
        case TYPE_STRING:
            return "TYPE_STRING";
        case TYPE_BLOB:
            return "TYPE_BLOB";
        default:
            return "?";
        }
    }
};

template<>
struct IsEnum<FieldType::Value> : TrueType {
    typedef FieldType Wrapper;
};

#endif
