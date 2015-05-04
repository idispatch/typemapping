#include <iostream>
#include "typetraits.h"
#include "objectbuffer.h"

#include "account.h"
#include "customer.h"

#include "sqlcursor.h"

#include "mappingitem.h"
#include "mappingsequence.h"

#include "cursorreader.h"

#include "connection.h"
#include "connectionfactory.h"
#include "connectionpool.h"
#include "command.h"

// Case 1:
//  using length as a prefix
// Case 2:
//  using terminator at the end (always the same)

// vectors of primitives
// vectors of complex types (of primitives)
// nullables

// Generated table
const MappingItem sequence_1[] ={
    MappingItem(8),
    MappingItem(Customer::F_NOTES, 0, 17),
    MappingItem(Customer::F_NOTES, 1, 18),
    MappingItem(Customer::F_NOTES, 2, 19),
    MappingItem(Customer::F_NOTES, 3, 20),
    MappingItem(Customer::F_ID,          0),
    MappingItem(Customer::F_FIRST_NAME,  1),
    MappingItem(Customer::F_LAST_NAME,   2),
    MappingItem(Customer::F_AGE,         3),
    MappingItem(Customer::F_DATE_JOINED, 4),

    /*
    {Customer::F_ACCOUNT_PRIMARY,    -1},

    {6, -1},
    {Account::F_ACCOUNT_NAME,         5},
    {Account::F_ACCOUNT_ID,           6},
    {Account::F_ACCOUNT_TYPE,         7},
    {Account::F_ACCOUNT_AMOUNT,       8},
    {Account::F_ACCOUNT_DATE_OPENED,  9},
    {Account::F_ACCOUNT_ACTIVE,      10},

    {Customer::F_ACCOUNT_SECONDARY,  -1},

    {6, -1},
    {Account::F_ACCOUNT_NAME,        11},
    {Account::F_ACCOUNT_ID,          12},
    {Account::F_ACCOUNT_TYPE,        13},
    {Account::F_ACCOUNT_AMOUNT,      14},
    {Account::F_ACCOUNT_DATE_OPENED, 15},
    {Account::F_ACCOUNT_ACTIVE,      16}*/
};

int main()
{
    MappingSequence mapping(sequence_1,
                            sizeof(sequence_1)/sizeof(sequence_1[0]));

    Customer customer;

    /*CursorReader reader(mapping, &cursor);
    reader(customer);
*/

    ConnectionPool::Ptr connectionPool;
    ConnectionPool::instance(&connectionPool);
    Connection::Ptr connection;
    connectionPool->connect("/Users/okosenkov/build-STL-Desktop_Qt_5_2_0_clang_64bit-Debug/clients.sqlite", &connection);

    std::cout << "isOpen: " << connection->isOpen() << std::endl;

    Command::Ptr command;
    connection->createCommand("SELECT clientId, firstName, lastName FROM clients",
                              &command);

    Cursor::Ptr cursor;
    command->execute(&cursor);

    while(cursor->next()) {
        int clientId;
        std::string firstName;
        std::string lastName;

        cursor->getValue(0, &clientId);
        cursor->getValue(1, &firstName);
        cursor->getValue(2, &lastName);

        std::cout << "id: " << clientId
                  << ", firstName: " << firstName
                  << ", lastName: " << lastName
                  << std::endl;
    }

    connection->close();

    ConnectionPool::clearAllPools();
    return 0;
}

