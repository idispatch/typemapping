#ifndef MAPPINGITEM_H
#define MAPPINGITEM_H

struct MappingItem {
    int d_fieldId;
    int d_columnId;

    int fieldId() const {
        return d_fieldId;
    }
    int columnId() const {
        return d_columnId;
    }
};

#endif // MAPPINGITEM_H
