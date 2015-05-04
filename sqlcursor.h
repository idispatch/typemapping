#ifndef INCLUDED_SQLCURSOR_H
#define INCLUDED_SQLCURSOR_H

#include <sqlite3.h>
#include "cursor.h"

//TODO: Error source (code/info)
//TODO: Supports properties

class SqlCursor : public Cursor {
    friend class SqlCommand;

    sqlite3_stmt *d_statement;
    bool d_beforeFirst;
    bool d_afterLast;

    SqlCursor(sqlite3_stmt *statement);
public:
    bool close();

    bool next();

    bool isClosed();

    bool isBeforeFirst();

    bool isAfterLast();

    bool columnCount(int *result);

    bool getType(int index, FieldType::Value * result);

    virtual bool isNull(int index);

    bool getValue(int index, bool * result);

    bool getValue(int index,          char * result);

    bool getValue(int index, signed   char * result);

    bool getValue(int index, unsigned char * result);

    bool getValue(int index, signed   short * result);

    bool getValue(int index, unsigned short * result);

    bool getValue(int index, signed   int * result);

    bool getValue(int index, unsigned int * result);

    bool getValue(int index, signed   long long * result);

    bool getValue(int index, unsigned long long * result);

    bool getValue(int index, float * result);

    bool getValue(int index, double * result);

    bool getValue(int index, std::string * result);

    bool getValue(int index, Datetime * result);

    bool getValue(int index, DatetimeTz * result);
};

#endif
