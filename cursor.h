#ifndef INCLUDED_CURSOR_H
#define INCLUDED_CURSOR_H

#include <string>
#include <memory>
#include "fieldtype.h"
#include "datetime.h"
#include "datetimetz.h"

class Cursor {
public:
    // PUBLIC TYPES
    typedef std::shared_ptr<Cursor> Ptr;

    // CREATORS
    virtual ~Cursor();
        // Destroy this object.

    // ACCESSORS
    virtual bool isClosed() = 0;
        // Return 'true' if the connection is closed and 'false' otherwise.

    virtual bool isBeforeFirst() = 0;
        // Return 'true' if the cursor points to the row before the first one
        // 'false' otherwise.

    virtual bool isAfterLast() = 0;
        // Return 'true' if the cursor points to the row after the last one
        // 'false' otherwise.

    virtual bool columnCount(int *result) = 0;

    virtual bool getType(int index, FieldType::Value * result) = 0;

    virtual bool isNull(int index) = 0;

    virtual bool getValue(int index, bool * result) = 0;

    virtual bool getValue(int index,          char * result) = 0;

    virtual bool getValue(int index, signed   char * result) = 0;

    virtual bool getValue(int index, unsigned char * result) = 0;

    virtual bool getValue(int index, signed   short * result) = 0;

    virtual bool getValue(int index, unsigned short * result) = 0;

    virtual bool getValue(int index, signed   int * result) = 0;

    virtual bool getValue(int index, unsigned int * result) = 0;

    virtual bool getValue(int index, signed   long long * result) = 0;

    virtual bool getValue(int index, unsigned long long * result) = 0;

    virtual bool getValue(int index, float * result) = 0;

    virtual bool getValue(int index, double * result) = 0;

    virtual bool getValue(int index, std::string * result) = 0;

    virtual bool getValue(int index, Datetime * result) = 0;

    virtual bool getValue(int index, DatetimeTz * result) = 0;

    // MANIPULATORS
    virtual bool close() = 0;
        // Close this cursor object and releases associated resources.

    virtual bool next() = 0;
        // Advance the cursor position to the next row.  Return 'true' on
        // success and 'false' otherwise.

};

#endif // CURSOR_H
