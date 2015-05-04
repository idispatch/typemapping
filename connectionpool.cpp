#include "connectionpool.h"
#include "connectionfactory.h"

std::tr1::shared_ptr<ConnectionPool> ConnectionPool::s_instance;

bool ConnectionPool::instance(ConnectionPool::Ptr * pool) {
    if(!s_instance) {
        s_instance.reset(new ConnectionPool());
    }
}

bool ConnectionPool::connect(const char *connectionString,
                             Connection::Ptr * connection) {
    if(!d_connection.get()) {
        if(!ConnectionFactory::connect(connectionString,
                                       &d_connection)) {
            return false;
        }
    }
    *connection = d_connection;
    return (*connection).get() != NULL;
}

void ConnectionPool::clearAllPools() {
    if(s_instance) {
        s_instance->d_connection.reset();
    }
}
