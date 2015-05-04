#ifndef INCLUDED_SQLCONNECTION_H
#define INCLUDED_SQLCONNECTION_H

#include "connection.h"
#include <sqlite3.h>

//TODO: Error source (code/info)
//TODO: Supports properties

                        // ===================
                        // class SqlConnection
                        // ===================

class SqlConnection : public Connection {
        // Concrete implementation of Conenction protocol
        // to access SQLite data source.

    // INSTANCE DATA
    sqlite3     *d_dbHandle;
    std::string  d_connectionString;
public:
    // CREATORS
    SqlConnection();
    ~SqlConnection();
        // Destroy this object.

    // ACCESSORS
    const std::string& connectionString() const;

    bool isOpen();

    // MANIPULATORS
    bool open(const std::string& connectionString);

    void close();

    bool createCommand(Command::Ptr *command);

    bool createCommand(const char *query,
                       Command::Ptr *command);
private:
    void closeConnection();
};

#endif
