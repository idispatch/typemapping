#ifndef INDEXEDFIELDSET_H
#define INDEXEDFIELDSET_H

#include <string>
#include "datetime.h"
#include "datetimetz.h"
#include "indexedtypeset.h"

class IndexedFieldSet : public IndexedTypeSet {
public:
    virtual ~IndexedFieldSet();

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
};

#endif // INDEXEDFIELDSET_H
