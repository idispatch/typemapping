#ifndef CURSOR_H
#define CURSOR_H

#include <string>
#include <memory>
#include "indexedfieldset.h"

class Cursor : public IndexedFieldSet {
public:

    typedef std::shared_ptr<Cursor> Ptr;

    virtual ~Cursor();

    virtual bool close() = 0;
    virtual bool next() = 0;

    virtual bool isClosed() = 0;
    virtual bool isBeforeFirst() = 0;
    virtual bool isAfterLast() = 0;
};

#endif // CURSOR_H
