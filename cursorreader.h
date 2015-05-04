#ifndef CursorReader_H
#define CursorReader_H

#include <string>
#include <vector>
#include "typetraits.h"
#include "datetime.h"
#include "mappingsequence.h"
#include "cursor.h"

class CursorReader {
    const MappingSequence&  d_mapping;
    int                     d_index;
    Cursor                 *d_cursor;
public:
    CursorReader(const MappingSequence &mapping,
                 Cursor *cursor)
        : d_mapping(mapping),
          d_index(0),
          d_cursor(cursor)
    {}

    template<typename T>
    int operator()(T& value);

    template<typename T>
    int operator()(std::vector<T>& value);

    int operator()(bool value);

    int operator()(         char value);
    int operator()(signed   char value);
    int operator()(unsigned char value);

    int operator()(signed   short value);
    int operator()(unsigned short value);

    int operator()(signed   int value);
    int operator()(unsigned int value);

    int operator()(signed   long long value);
    int operator()(unsigned long long value);

    int operator()(float  value);
    int operator()(double value);

private:
    template<typename T>
    int handle(T& value, category_unknown);

    template<typename T>
    int handle(T& value, category_nullable);

    template<typename T>
    int handle(T& value, category_primitive);

    template<typename T>
    int handle(T& value, category_enumeration);

    template<typename T>
    int handle(T& value, category_sequence);

    template<typename T>
    int handle(T& value, category_choice);

    template<typename T>
    int handleNull(T& value);

    template<typename T>
    bool readFromCursor(T *value);
};


template<typename T>
bool CursorReader::readFromCursor(T *value) {
    const int columnId = d_mapping[d_index].columnId();

    FieldType::Value fieldType;
    if(d_cursor->getType(columnId, &fieldType)) {
        std::cout << "(cursor index:" << columnId
                  << ", type:" << FieldType::toString(fieldType) <<")"
                  << std::endl;
    } else {
        std::cout << "Could not get column type at column "
                  << columnId << std::endl;
    }

    return d_cursor->getValue(columnId, value);
}

template<typename T>
int CursorReader::handleNull(T& value) {
    int rc;
    if(d_cursor->isNull(d_mapping[d_index].columnId())) {
        value.reset();
        rc = 0;
    } else {
        rc = readFromCursor(&value.value());
    }
    std::cout << "NULL:" << value << std::endl;
    return rc;
}

template<typename T>
int CursorReader::handle(T& value, category_primitive) {
    return operator ()(value);
}

template<typename T>
int CursorReader::handle(T& value, category_nullable) {
    if(value.isNull()) {
        return handleNull(value);
    } else {
        return operator()(value.value());
    }
}

template<typename T>
int CursorReader::handle(T& value, category_enumeration) {
    typedef typename IsEnum<T>::Wrapper EnumType;
    return operator ()(EnumType::toInt(value));
}

template<typename T>
int CursorReader::handle(T& value, category_sequence) {
    int count = d_mapping[d_index++].numAttributes();
    int result = 0;
    for(int i = 0; result >= 0 && i < count; i++) {
        //const MappingItem& m = d_mapping[d_index++];
        const MappingItem& m = d_mapping[d_index];
        result = value.manipulate(*this, m.fieldId());
        d_index++;
    }
    return result;
}

template<typename T>
int CursorReader::handle(T& value, category_choice) {
    std::cout << "CHOICE: " << value << std::endl;
    return -1;
}

template<typename T>
int CursorReader::handle(T& value, category_unknown) {
    std::cout << "UNKNOWN: " << value << std::endl;
    return -1;
}

template<typename T>
int CursorReader::operator()(std::vector<T>& value) {
    int index = d_mapping[d_index].index();
    if(index <= value.size()) {
        value.resize(index + 1);
    }
    bool rc = readFromCursor(&value[index]);
    return rc ? 0 : -1;

}

template<typename T>
int CursorReader::operator()(T& value) {
    return handle(value, typename category<T>::Value());
}

int CursorReader::operator()(bool value) {
    bool rc = readFromCursor(&value);
    std::cout << "bool:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(char value) {
    bool rc = readFromCursor(&value);
    std::cout << "char:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(signed char value) {
    bool rc = readFromCursor(&value);
    std::cout << "signed char:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(unsigned char value) {
    bool rc = readFromCursor(&value);
    std::cout << "unsigned char:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(signed short value) {
    bool rc = readFromCursor(&value);
    std::cout << "signed short:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(unsigned short value) {
    bool rc = readFromCursor(&value);
    std::cout << "unsigned short:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(signed int value) {
    bool rc = readFromCursor(&value);
    std::cout << "signed int:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(unsigned int value) {
    bool rc = readFromCursor(&value);
    std::cout << "unsigned int:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(signed long long value) {
    bool rc = readFromCursor(&value);
    std::cout << "signed long long:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(unsigned long long value) {
    bool rc = readFromCursor(&value);
    std::cout << "unsigned long long:" << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(float value) {
    bool rc = readFromCursor(&value);
    std::cout << "float: " << value << std::endl;
    return rc ? 0 : -1;
}

int CursorReader::operator()(double value) {
    bool rc = readFromCursor(&value);
    std::cout << "double: " << value << std::endl;
    return rc ? 0 : -1;
}

template<>
int CursorReader::operator()(Datetime& value) {
    bool rc = readFromCursor(&value);
    std::cout << "datetime: " << value << std::endl;
    return rc ? 0 : -1;
}

template<>
int CursorReader::operator()(DatetimeTz& value) {
    bool rc = readFromCursor(&value);
    std::cout << "datetimetz: " << value << std::endl;
    return rc ? 0 : -1;
}

template<>
int CursorReader::operator()(std::string& value) {
    bool rc = readFromCursor(&value);
    std::cout << "string:" << value << std::endl;
    return rc ? 0 : -1;
}


#endif // CursorReader_H
