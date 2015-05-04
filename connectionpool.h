#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <memory>
#include "connection.h"


class ConnectionPool {
    // ConnectionPool uses ConnectionFactory to create connection and pool them

    // CLASS DATA
    static std::shared_ptr<ConnectionPool> s_instance;

    // INSTANCE DATA
    Connection::Ptr d_connection; // TODO: replace with map
public:
    // PUBLIC TYPES
    typedef std::shared_ptr<ConnectionPool> Ptr;

    // CLASS ACCESSORS
    static ConnectionPool::Ptr instance();
        // Return the shared pointer to the default connection pool instance.

    static void clearAllPools();
        // Removes all pooled connection from all connection pools.

    // MANIPULATORS
    bool connect(const char *connectionString,
                 Connection::Ptr * connection);
        // Obtain the database connection and if the connection is successfully
        // retrieved pool it in this pool.  Return 'true' if the connection was
        // successfully obtained and 'false' otherwise.

    void clearPool();
        // Removes all pooled connections from this pool.
};

#endif // CONNECTIONPOOL_H
