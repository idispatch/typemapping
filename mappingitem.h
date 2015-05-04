#ifndef MAPPINGITEM_H
#define MAPPINGITEM_H

class MappingItem {
    int d_numAttributes; // only for Complex types
    int d_fieldId;       // attribute id in complex type
    int d_index;         // index in the attribute of type vector
    int d_columnId;      // source/destination column id
public:
    MappingItem(int numAttributes)
        : d_numAttributes(numAttributes),
        d_index(-1),
        d_fieldId(-1),
        d_columnId(-1) {
    }
    MappingItem(int fieldId,
                int columnId)
        : d_numAttributes(1),
          d_index(0),
          d_fieldId(fieldId),
          d_columnId(columnId) {
    }
    MappingItem(int fieldId,
                int index,
                int columnId)
        : d_numAttributes(1),
          d_index(index),
          d_fieldId(fieldId),
          d_columnId(columnId) {
    }

    int numAttributes() const {
        return d_numAttributes;
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

#endif // MAPPINGITEM_H
