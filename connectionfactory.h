#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include "connection.h"


class ConnectionFactory {
    // ConnectionFactory is an utility to create connections
public:
    static bool connect(const char *connectionString,
                        Connection::Ptr *connection);
};

#endif // CONNECTIONFACTORY_H
