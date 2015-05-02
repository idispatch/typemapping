#ifndef CURSOR_H
#define CURSOR_H

#include <string>
#include "indexedfieldset.h"

class ReadOnlyCursor : public IndexedFieldSet {
public:
    virtual ~ReadOnlyCursor();

    virtual bool close() = 0;
    virtual bool next() = 0;

    virtual bool isClosed() = 0;
    virtual bool isBeforeFirst() = 0;
    virtual bool isAfterLast() = 0;
};

#endif // CURSOR_H
