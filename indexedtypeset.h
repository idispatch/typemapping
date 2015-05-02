#ifndef INDEXEDTYPESET_H
#define INDEXEDTYPESET_H

#include "fieldtype.h"

class IndexedTypeSet {
public:
    virtual ~IndexedTypeSet();

    virtual bool getType(int index, FieldType::Value * result) = 0;
};

#endif // INDEXEDTYPESET_H
