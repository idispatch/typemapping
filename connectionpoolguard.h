#ifndef INCLUDED_CONNECTIONPOOLGUARD_H
#define INCLUDED_CONNECTIONPOOLGUARD_H

#include "connectionpool.h"

class ConnectionPoolGuard {
    ConnectionPool::Ptr d_connectionPool;
public:
    ConnectionPoolGuard(ConnectionPool::Ptr connectionPool);
    ~ConnectionPoolGuard();
};

#endif // CONNECTIONPOOLGUARD_H
