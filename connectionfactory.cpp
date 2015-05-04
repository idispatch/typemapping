#include "connectionfactory.h"
#include "sqlconnection.h"

bool ConnectionFactory::connect(const char *connectionString,
                                Connection::Ptr *connection)
{
    connection->reset(new SqlConnection());
    return (*connection)->open(connectionString);
}

