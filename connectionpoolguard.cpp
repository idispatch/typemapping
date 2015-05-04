#include "connectionpoolguard.h"

ConnectionPoolGuard::ConnectionPoolGuard(ConnectionPool::Ptr connectionPool)
    : d_connectionPool(connectionPool)
{}

ConnectionPoolGuard::~ConnectionPoolGuard()
{
    if(d_connectionPool) {
        d_connectionPool->clearPool();
        d_connectionPool.reset();
    }
}
