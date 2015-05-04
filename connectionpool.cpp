#include "connectionpool.h"
#include "connectionfactory.h"

ConnectionPool::Ptr ConnectionPool::s_instance;

ConnectionPool::Ptr ConnectionPool::instance() {
    // TODO: initialize once
    if(!s_instance) {
        s_instance.reset(new ConnectionPool());
    }
    return s_instance;
}

bool ConnectionPool::connect(const char *connectionString,
                             Connection::Ptr * connection) {
    if(!d_connection) {
        if(!ConnectionFactory::connect(connectionString,
                                       &d_connection)) {
            return false;
        }
    }
    *connection = d_connection;
    return (*connection);
}

void ConnectionPool::clearPool() {
    d_connection.reset();
}

void ConnectionPool::clearAllPools() {
    if(s_instance) {
        s_instance->d_connection.reset();
    }
}
