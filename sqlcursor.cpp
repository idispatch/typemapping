#include "sqlcursor.h"

SqlCursor::SqlCursor(sqlite3_stmt *statement)
    : d_statement(statement),
      d_beforeFirst(false),
      d_afterLast(false)
{}

bool SqlCursor::close() {
    d_statement = NULL;
    d_beforeFirst = false;
    d_afterLast = false;
    return true;
}

bool SqlCursor::next() {
    int rc = ::sqlite3_step(d_statement);
    d_beforeFirst = false;
    d_afterLast = (rc == SQLITE_DONE);
    return rc == SQLITE_ROW;
}

bool SqlCursor::isClosed() {
    return d_statement == NULL;
}

bool SqlCursor::isBeforeFirst() {
    return d_beforeFirst;
}

bool SqlCursor::isAfterLast() {
    return d_afterLast;
}

bool SqlCursor::getType(int index, FieldType::Value *result) {
    bool rc = true;

    const int columnType = ::sqlite3_column_type(d_statement, index);
    switch(columnType) {
    case SQLITE_INTEGER:
        *result = FieldType::TYPE_SIGNED_LONG_LONG;
        break;
    case SQLITE_FLOAT:
        *result = FieldType::TYPE_DOUBLE;
        break;
    case SQLITE_BLOB:
        *result = FieldType::TYPE_BLOB;
        break;
    case SQLITE_TEXT:
        *result = FieldType::TYPE_STRING;
        break;
    case SQLITE_NULL:
        *result = FieldType::TYPE_NULL;
        break;
    default:
        rc = false;
    }
    return rc;
}

bool SqlCursor::isNull(int index) {
    return ::sqlite3_column_type(d_statement, index) == SQLITE_NULL;
}

bool SqlCursor::getValue(int index, bool * result) {
    int value = ::sqlite3_column_int(d_statement, index);
    *result = value != 0;
    return true;
}

bool SqlCursor::getValue(int index, char *result) {
    int value = ::sqlite3_column_int(d_statement, index);
    *result = static_cast<char>(value);
    return true;
}

bool SqlCursor::getValue(int index, signed char *result) {
    int value = ::sqlite3_column_int(d_statement, index);
    *result = static_cast<signed char>(value);
    return true;
}

bool SqlCursor::getValue(int index, unsigned char *result) {
    int value = ::sqlite3_column_int(d_statement, index);
    *result = static_cast<unsigned char>(value);
    return true;
}

bool SqlCursor::getValue(int index, signed short *result) {
    int value = ::sqlite3_column_int(d_statement, index);
    *result = static_cast<signed short>(value);
    return true;
}

bool SqlCursor::getValue(int index, unsigned short *result) {
    int value = ::sqlite3_column_int(d_statement, index);
    *result = static_cast<unsigned short>(value);
    return true;
}

bool SqlCursor::getValue(int index, signed int *result) {
    int value = ::sqlite3_column_int(d_statement, index);
    *result = static_cast<signed int>(value);
    return true;
}

bool SqlCursor::getValue(int index, unsigned int *result) {
    sqlite3_int64 value = ::sqlite3_column_int64(d_statement, index);
    *result = static_cast<unsigned int>(value);
    return true;
}

bool SqlCursor::getValue(int index, signed long long *result) {
    sqlite3_int64 value = ::sqlite3_column_int64(d_statement, index);
    *result = static_cast<signed long long>(value);
    return true;
}

bool SqlCursor::getValue(int index, unsigned long long *result) {
    sqlite3_int64 value = ::sqlite3_column_int64(d_statement, index);
    *result = static_cast<unsigned long long>(value);
    return true;
}

bool SqlCursor::getValue(int index, float *result) {
    double value = sqlite3_column_double(d_statement, index);
    *result = static_cast<float>(value);
    return true;
}

bool SqlCursor::getValue(int index, double *result) {
    *result = sqlite3_column_double(d_statement, index);
    return true;
}

bool SqlCursor::getValue(int index, std::string *result) {
    int count = ::sqlite3_column_bytes(d_statement, index);
    const unsigned char * value = ::sqlite3_column_text(d_statement, index);
    const char *begin = reinterpret_cast<const char*>(value);
    result->assign(begin, begin + count);
    return true;
}

bool SqlCursor::getValue(int, Datetime *) {
    return true;
}

bool SqlCursor::getValue(int, DatetimeTz *) {
    return true;
}

bool SqlCursor::columnCount(int *result) {
    *result = sqlite3_column_count(d_statement);
    return true;
}
