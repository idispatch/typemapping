#ifndef INCLUDED_OBJECT_READER_H
#define INCLUDED_OBJECT_READER_H

#include <string>
#include <vector>
#include "typetraits.h"
#include "datetime.h"
#include "mappingsequence.h"
#include "cursor.h"

class ObjectReader {
    const MappingSequence&  d_mapping;
    int                     d_index;
    Cursor::Ptr             d_cursor;
public:
    ObjectReader(const MappingSequence &mapping,
                 Cursor::Ptr cursor)
        : d_mapping(mapping),
          d_index(0),
          d_cursor(cursor)
    {}

    template<typename T>
    int operator()(T *value);

    template<typename T>
    int operator()(std::vector<T> *value);

    int operator()(bool *value);

    int operator()(         char *value);
    int operator()(signed   char *value);
    int operator()(unsigned char *value);

    int operator()(signed   short *value);
    int operator()(unsigned short *value);

    int operator()(signed   int *value);
    int operator()(unsigned int *value);

    int operator()(signed   long long *value);
    int operator()(unsigned long long *value);

    int operator()(float  *value);
    int operator()(double *value);

    void reset();
private:
    template<typename T>
    int handle(T *value, Category_Unknown);

    template<typename T>
    int handle(T *value, Category_Nullable);

    template<typename T>
    int handle(T *value, Category_Primitive);

    template<typename T>
    int handle(T *value, Category_Enumeration);

    template<typename T>
    int handle(T *value, Category_Sequence);

    template<typename T>
    int handle(T *value, Category_Choice);

    template<typename T>
    int handleNull(T *value);

    template<typename T>
    bool readFromCursor(T *value);
};

void ObjectReader::reset() {
    d_index = 0;
}

template<typename T>
bool ObjectReader::readFromCursor(T *value) {
    const int columnId = d_mapping[d_index].columnId();
#if 0
    FieldType::Value fieldType;
    if(d_cursor->getType(columnId, &fieldType)) {
        std::cout << "(cursor index:" << columnId
                  << ", type:" << FieldType::toString(fieldType) <<")"
                  << std::endl;
    } else {
        std::cout << "Could not get column type at column "
                  << columnId << std::endl;
    }
#endif
    return d_cursor->getValue(columnId, value);
}

template<typename T>
int ObjectReader::handleNull(T *value) {
    int rc;
    if(d_cursor->isNull(d_mapping[d_index].columnId())) {
        value->reset();
        rc = 0;
    } else {
        rc = readFromCursor(&value->value());
    }
    //std::cout << "NULL:" << *value << std::endl;
    return rc;
}

template<typename T>
int ObjectReader::handle(T *value, Category_Primitive) {
    return operator ()(value);
}

template<typename T>
int ObjectReader::handle(T *value, Category_Nullable) {
    if(value->isNull()) {
        return handleNull(value);
    } else {
        return operator()(&value->value());
    }
}

template<typename T>
int ObjectReader::handle(T *value, Category_Enumeration) {
    int result;
    bool rc = operator ()(&result);
    typedef typename IsEnum<T>::Wrapper EnumType;
    if(rc) {
        *value = EnumType::fromInt(result);
    }
    return rc;
}

template<typename T>
int ObjectReader::handle(T *value, Category_Sequence) {
    int result = 0;
    for(; result >= 0 && !d_mapping[d_index].isAfterLast(); ++d_index) {
        result = value->manipulate(*this, d_mapping[d_index].fieldId());
    }
    return result;
}

template<typename T>
int ObjectReader::handle(T *value, Category_Choice) {
    std::cout << "CHOICE: " << *value << std::endl;
    return -1;
}

template<typename T>
int ObjectReader::handle(T *value, Category_Unknown) {
    std::cout << "UNKNOWN: " << *value << std::endl;
    return -1;
}

template<typename T>
int ObjectReader::operator()(std::vector<T> *value) {
    std::size_t index = d_mapping[d_index].index();
    if(index <= value->size()) {
        value->resize(index + 1);
    }
    bool rc = readFromCursor(&(*value)[index]);
    return rc ? 0 : -1;
}

template<typename T>
int ObjectReader::operator()(T *value) {
    return handle(value, typename category<T>::Value());
}

int ObjectReader::operator()(bool *value) {
    bool rc = readFromCursor(value);
    //std::cout << "bool:" << *value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(char *value) {
    bool rc = readFromCursor(value);
    //std::cout << "char:" << *value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(signed char *value) {
    bool rc = readFromCursor(value);
    //std::cout << "signed char:" << *value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(unsigned char *value) {
    bool rc = readFromCursor(value);
    //std::cout << "unsigned char:" << value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(signed short *value) {
    bool rc = readFromCursor(value);
    //std::cout << "signed short:" << value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(unsigned short *value) {
    bool rc = readFromCursor(value);
    //std::cout << "unsigned short:" << *value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(signed int *value) {
    bool rc = readFromCursor(value);
    //std::cout << "signed int:" << *value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(unsigned int *value) {
    bool rc = readFromCursor(value);
    //std::cout << "unsigned int:" << *value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(signed long long *value) {
    bool rc = readFromCursor(value);
    //std::cout << "signed long long:" << value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(unsigned long long *value) {
    bool rc = readFromCursor(value);
    //std::cout << "unsigned long long:" << *value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(float *value) {
    bool rc = readFromCursor(value);
    //std::cout << "float: " << *value << std::endl;
    return rc ? 0 : -1;
}

int ObjectReader::operator()(double *value) {
    bool rc = readFromCursor(value);
    //std::cout << "double: " << *value << std::endl;
    return rc ? 0 : -1;
}

template<>
int ObjectReader::operator()(Datetime *value) {
    bool rc = readFromCursor(value);
    //std::cout << "datetime: " << *value << std::endl;
    return rc ? 0 : -1;
}

template<>
int ObjectReader::operator()(DatetimeTz *value) {
    bool rc = readFromCursor(value);
    //std::cout << "datetimetz: " << *value << std::endl;
    return rc ? 0 : -1;
}

template<>
int ObjectReader::operator()(std::string *value) {
    bool rc = readFromCursor(value);
    //std::cout << "string:" << *value << std::endl;
    return rc ? 0 : -1;
}

#endif
