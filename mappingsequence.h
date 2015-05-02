#ifndef MAPPINGSEQUENCE_H
#define MAPPINGSEQUENCE_H

#include "mappingitem.h"

class MappingSequence {
    const int d_n;
    const MappingItem *d_mi;
public:
    MappingSequence(const MappingItem *mi, int n)
        :d_n(n),d_mi(mi) {
    }

    const MappingItem& operator [](int i) const {
        return d_mi[i];
    }

    int count() const {
        return d_n;
    }
};

#endif // MAPPINGSEQUENCE_H
