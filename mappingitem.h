#ifndef INCLUDED_MAPPINGITEM_H
#define INCLUDED_MAPPINGITEM_H

class MappingItem {
public:
    // INSTANCE DATA
    int d_fieldId;       // attribute id in complex type
    int d_columnId;      // source/destination column id
    int d_index;         // index in the attribute of type vector


    // CREATORS
    /*MappingItem()
        : d_index(-1),
          d_fieldId(-1),
          d_columnId(-1)
    {}
    MappingItem(int fieldId,
                int columnId)
        : d_index(0),
          d_fieldId(fieldId),
          d_columnId(columnId) {
    }
    MappingItem(int fieldId,
                int index,
                int columnId)
        : d_index(index),
          d_fieldId(fieldId),
          d_columnId(columnId) {
    }*/

    // ACCESSORS
    bool isAfterLast() const {
        return d_columnId == -1 && d_fieldId == -1;
    }

    int fieldId() const {
        return d_fieldId;
    }

    int index() const {
        return d_index;
    }

    int columnId() const {
        return d_columnId;
    }
};

#endif
