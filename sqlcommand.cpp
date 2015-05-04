#include "sqlcommand.h"
#include "sqlcursor.h"

SqlCommand::SqlCommand(sqlite3 *dbHandle)
    : d_dbHandle(dbHandle),
      d_statement(NULL) {
}

SqlCommand::SqlCommand(sqlite3_stmt *statement)
    : d_statement(statement) {
    d_dbHandle = ::sqlite3_db_handle(statement);
}

SqlCommand::~SqlCommand() {
    closeCommand();
}

void SqlCommand::closeCommand() {
    if(d_statement) {
        ::sqlite3_finalize(d_statement);
        d_statement = NULL;
    }
}

bool SqlCommand::bindNull(int index) {
    int rc = ::sqlite3_bind_null(d_statement, index);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, bool value) {
    int rc = ::sqlite3_bind_int(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, char value) {
    int rc = ::sqlite3_bind_int(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, signed char value) {
    int rc = ::sqlite3_bind_int(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, unsigned char value) {
    int rc = ::sqlite3_bind_int(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, signed short value) {
    int rc = ::sqlite3_bind_int(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, unsigned short value) {
    int rc = ::sqlite3_bind_int(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, signed int value) {
    int rc = ::sqlite3_bind_int(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, unsigned int value) {
    int rc = ::sqlite3_bind_int64(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, signed long long value) {
    int rc = ::sqlite3_bind_int64(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, unsigned long long value) {
    int rc = ::sqlite3_bind_int64(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, float value) {
    return bind(index, static_cast<double>(value));
}

bool SqlCommand::bind(int index, double value) {
    int rc = ::sqlite3_bind_double(d_statement, index, value);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, const std::string& value) {
    int rc = ::sqlite3_bind_text(d_statement,
                                 index,
                                 value.c_str(),
                                 value.length(),
                                 SQLITE_STATIC);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, const std::vector<char>& value) {
    const char * p;
    if(value.empty()) {
        p = NULL;
    } else {
        p = value.data();
    }
    int rc = ::sqlite3_bind_blob(d_statement,
                                 index,
                                 p,
                                 value.size(),
                                 SQLITE_STATIC);
    return rc == SQLITE_OK;
}

bool SqlCommand::bind(int index, const Datetime& value) {
    return true;
}

bool SqlCommand::bind(int index, const DatetimeTz& value) {
    return true;
}

bool SqlCommand::reset() {
    int rc;
    if(d_statement) {
        rc = ::sqlite3_reset(d_statement);
        rc = ::sqlite3_clear_bindings(d_statement);
    } else {
        rc = SQLITE_ERROR;
    }
    return rc == SQLITE_OK;
}

bool SqlCommand::execute(const char *query,
                         Cursor::Ptr *cursor)
{
    closeCommand();
    int rc = ::sqlite3_prepare_v2(d_dbHandle,
                                  query,
                                  -1,
                                  &d_statement,
                                  NULL);
    if(rc) {
        return false;
    }

    return execute(cursor);
}

bool SqlCommand::execute(Cursor::Ptr *cursor)
{
    if(d_statement == NULL) {
        return false;
    }
    cursor->reset(new SqlCursor(d_statement));
    return true;
}
