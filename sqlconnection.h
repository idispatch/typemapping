#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include "connection.h"
#include <sqlite3.h>

class SqlConnection : public Connection {
    sqlite3 *d_dbHandle;

    void closeConnection();

public:
    SqlConnection();
    ~SqlConnection();

    bool open(const char *connectionString);

    void close();

    bool isOpen();

    bool createCommand(Command::Ptr *command);

    bool createCommand(const char *query,
                       Command::Ptr *command);
};

#endif // SQLCONNECTION_H
