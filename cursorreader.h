#ifndef CURSORREADER_H
#define CURSORREADER_H

#include "typetraits.h"
#include "datetime.h"
#include "mappingsequence.h"
#include "cursor.h"

class CursorReader {
    const MappingSequence&  d_mapping;
    int                     d_index;
    ReadOnlyCursor         *d_cursor;
public:
    CursorReader(const MappingSequence &mapping, ReadOnlyCursor *cursor)
        : d_mapping(mapping),
          d_index(0),
          d_cursor(cursor)
    {}

    template<typename T>
    int operator()(T& value);

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

    int handleNull();
};

int CursorReader::handleNull() {
   std::cout << "NULL: " << std::endl;
}

template<typename T>
int CursorReader::handle(T& value, category_primitive) {
    return operator ()(value);
}

template<typename T>
int CursorReader::handle(T& value, category_nullable) {
    if(value.isNull()) {
        return operator()(value.value());
    } else {
        return handleNull();
    }
}

template<typename T>
int CursorReader::handle(T& value, category_enumeration) {
    typedef typename IsEnum<T>::Wrapper EnumType;
    return operator ()(EnumType::toInt(value));
}

template<typename T>
int CursorReader::handle(T& value, category_sequence) {
    int count = d_mapping[d_index++].d_fieldId;
    int result = 0;
    for(int i = 0; result >= 0 && i < count; i++) {
        result = value.manipulate(*this, d_mapping[d_index++].d_fieldId);
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

int CursorReader::operator()(bool value) {
    std::cout << "bool:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(char value) {
    std::cout << "char:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(signed char value) {
    std::cout << "signed char:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(unsigned char value) {
    std::cout << "unsigned char:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(signed short value) {
    std::cout << "signed short:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(unsigned short value) {
    std::cout << "unsigned short:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(signed int value) {
    std::cout << "signed int:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(unsigned int value) {
    std::cout << "unsigned int:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(signed long long value) {
    std::cout << "signed long long:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(unsigned long long value) {
    std::cout << "unsigned long long:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(float value) {
    std::cout << "float:" << value << std::endl;
    return 0;
}

int CursorReader::operator()(double value) {
    std::cout << "double:" << value << std::endl;
    return 0;
}

template<>
int CursorReader::operator()(const Datetime& value) {
    std::cout << "datetime:"  << std::endl;
    return 0;
}

template<>
int CursorReader::operator()(const DatetimeTz& value) {
    std::cout << "datetimeTz:" << std::endl;
    return 0;
}

template<>
int CursorReader::operator()(std::string& value) {
    std::cout << "string:" << value << std::endl;
    return 0;
}

template<typename T>
int CursorReader::operator()(T& value) {
    typename category<T>::Value tag;
    return handle(value, tag);
}

#endif // CURSORREADER_H
