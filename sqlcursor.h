#ifndef SQLCURSOR_H
#define SQLCURSOR_H

#include "cursor.h"

class SqlCursor : public ReadOnlyCursor {
    bool d_closed;
public:
    SqlCursor()
        :d_closed(false)
    {}

    bool close() {
        d_closed  = true;
    }

    bool next() {
        return true;
    }

    bool isClosed() {
        return d_closed;
    }

    bool isBeforeFirst() {
        return false;
    }

    bool isAfterLast() {
        return false;
    }

    bool getType(int index, FieldType::Value * result) {
        *result = FieldType::TYPE_NULL;
        return false;
    }

    bool getValue(int index, bool * result) {
        *result = false;
        return true;
    }

    bool getValue(int index, signed   short * result) {
        *result = 4;
        return true;
    }

    bool getValue(int index, unsigned short * result) {
        *result = 4;
        return true;
    }

    bool getValue(int index, signed   int * result) {
        *result = 4;
        return true;
    }

    bool getValue(int index, unsigned int * result) {
        *result = 4;
        return true;
    }

    bool getValue(int index, signed   long long * result) {
        *result = 4;
        return true;
    }

    bool getValue(int index, unsigned long long * result) {
        *result = 4;
        return true;
    }

    bool getValue(int index, float * result) {
        *result = 4.0;
        return true;
    }

    bool getValue(int index, double * result) {
        *result = 4.0;
        return true;
    }

    bool getValue(int index, std::string * result) {
        *result = "4.0";
        return true;
    }

    bool getValue(int index, Datetime * result) {
        return true;
    }

    bool getValue(int index, DatetimeTz * result) {
        return true;
    }
};

#endif // SQLCURSOR_H
