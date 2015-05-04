#ifndef INDEXEDTYPESET_H
#define INDEXEDTYPESET_H

#include "fieldtype.h"

class IndexedTypeSet {
public:
    virtual ~IndexedTypeSet();

    virtual bool columnCount(int *result) = 0;

    virtual bool getType(int index, FieldType::Value * result) = 0;
};

#endif // INDEXEDTYPESET_H
