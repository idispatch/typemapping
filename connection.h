#ifndef INCLUDED_CONNECTION_H
#define INCLUDED_CONNECTION_H

#include <memory>
#include <string>
#include "command.h"

//TODO: last error support

                            // ================
                            // class Connection
                            // ================

class Connection {
    // class 'Connection' is a protocol for database connection

public:
    // PUBLIC TYPES
    typedef std::shared_ptr<Connection> Ptr;

    // CREATORS
    virtual ~Connection();

    // ACCESSORS
    virtual const std::string& connectionString() const = 0;

    virtual bool isOpen() = 0;

    // MANIPULATORS
    virtual bool open(const std::string& connectionString) = 0;

    virtual void close() = 0;

    virtual bool createCommand(Command::Ptr *command) = 0;

    virtual bool createCommand(const char *query,
                               Command::Ptr *command) = 0;
};

#endif
