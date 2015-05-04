#ifndef CONNECTION_H
#define CONNECTION_H

#include <memory>
#include "command.h"

class Connection {
public:
    typedef std::shared_ptr<Connection> Ptr;

    virtual ~Connection();

    virtual bool open(const char *connectionString) = 0;

    virtual bool isOpen() = 0;

    virtual void close() = 0;

    virtual bool createCommand(Command::Ptr *command) = 0;

    virtual bool createCommand(const char *query,
                               Command::Ptr *command) = 0;
};

#endif // CONNECTION_H
