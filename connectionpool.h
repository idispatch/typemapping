#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <tr1/memory>
#include "connection.h"

// ConnectionPool uses ConnectionFactory to create connection and pool them
class ConnectionPool {
    static std::tr1::shared_ptr<ConnectionPool> s_instance;

    Connection::Ptr d_connection; // TODO: replace with map
public:
    typedef std::tr1::shared_ptr<ConnectionPool> Ptr;

    static bool instance(ConnectionPool::Ptr * pool);

    static void clearAllPools();

    bool connect(const char *connectionString,
                 Connection::Ptr * connection);
};

#endif // CONNECTIONPOOL_H
