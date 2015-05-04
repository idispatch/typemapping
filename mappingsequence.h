#ifndef INCLUDED_MAPPINGSEQUENCE_H
#define INCLUDED_MAPPINGSEQUENCE_H

#include "mappingitem.h"

class MappingSequence {
    const MappingItem *d_mi;
public:
    MappingSequence(const MappingItem *mi)
        :d_mi(mi) {
    }

    const MappingItem& operator [](int i) const {
        return d_mi[i];
    }
};

#endif
