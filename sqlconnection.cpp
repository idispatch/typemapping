#include "sqlconnection.h"
#include "sqlcommand.h"

void SqlConnection::closeConnection() {
    if(d_dbHandle) {
        ::sqlite3_close(d_dbHandle);
        d_dbHandle = NULL;
    }
}

SqlConnection::SqlConnection()
    : d_dbHandle(NULL)
{}

SqlConnection::~SqlConnection() {
    closeConnection();
}

bool SqlConnection::open(const char *connectionString) {
    closeConnection();
    int rc = ::sqlite3_open(connectionString, &d_dbHandle);
    return rc == SQLITE_OK;
}

bool SqlConnection::isOpen() {
    return d_dbHandle != NULL;
}

void SqlConnection::close() {
    closeConnection();
}

bool SqlConnection::createCommand(Command::Ptr *command)
{
    command->reset(new SqlCommand(d_dbHandle));
    return true;
}

bool SqlConnection::createCommand(const char *query,
                                  Command::Ptr *command)
{
    sqlite3_stmt *statement = NULL;
    int rc = ::sqlite3_prepare_v2(d_dbHandle,
                                  query,
                                  -1,
                                  &statement,
                                  NULL);
    if(rc == SQLITE_OK) {
        command->reset(new SqlCommand(statement));
    }

    return rc == SQLITE_OK;
}
