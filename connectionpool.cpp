#include "connectionpool.h"
#include "connectionfactory.h"

ConnectionPool::Ptr ConnectionPool::s_instance;

bool ConnectionPool::instance(ConnectionPool::Ptr * pool) {
    if(!s_instance) {
        s_instance.reset(new ConnectionPool());
    }
    *pool = s_instance;
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
    return (*connection) != NULL;
}

void ConnectionPool::clearAllPools() {
    if(s_instance) {
        s_instance->d_connection.reset();
    }
}
