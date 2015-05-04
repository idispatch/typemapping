#include <iostream>

#include "account.h"
#include "customer.h"

#include "mappingitem.h"
#include "mappingsequence.h"

#include "connection.h"
#include "connectionfactory.h"
#include "connectionpool.h"
#include "connectionpoolguard.h"

#include "objectreader.h"
#include "command.h"

// Generated table
const MappingItem sequence_1[] ={
    MappingItem(Customer::F_ID,             0),
    MappingItem(Customer::F_FIRST_NAME,     1),
    MappingItem(Customer::F_LAST_NAME,      2),
    MappingItem(Customer::F_NOTES,       0, 3),
    MappingItem(Customer::F_NOTES,       1, 4),
    MappingItem(Customer::F_NOTES,       2, 5),
    MappingItem(Customer::F_NOTES,       3, 6),
    MappingItem()
    /*
    MappingItem(Customer::F_AGE,         3),
    MappingItem(Customer::F_DATE_JOINED, 4),
    MappingItem(Customer::F_ACCOUNT_PRIMARY),

    MappingItem(Account::F_ACCOUNT_NAME,         5),
    MappingItem(Account::F_ACCOUNT_ID,           6),
    MappingItem(Account::F_ACCOUNT_TYPE,         7),
    MappingItem(Account::F_ACCOUNT_AMOUNT,       8),
    MappingItem(Account::F_ACCOUNT_DATE_OPENED,  9),
    MappingItem(Account::F_ACCOUNT_ACTIVE,      10),
    MappingItem(),

    MappingItem(Customer::F_ACCOUNT_SECONDARY),

    MappingItem(Account::F_ACCOUNT_NAME,        11),
    MappingItem(Account::F_ACCOUNT_ID,          12),
    MappingItem(Account::F_ACCOUNT_TYPE,        13),
    MappingItem(Account::F_ACCOUNT_AMOUNT,      14),
    MappingItem(Account::F_ACCOUNT_DATE_OPENED, 15),
    MappingItem(Account::F_ACCOUNT_ACTIVE,      16),
    MappingItem()*/
};


void testDatabase()
{
    // Obtain defaul connection pool instance
    ConnectionPool::Ptr connectionPool = ConnectionPool::instance();

    // Optionally setup connection pool guard (will clean pool one exit)
    ConnectionPoolGuard poolGuard(connectionPool);

    // Get database connection from the connection pool
    Connection::Ptr connection;
    connectionPool->connect("clients.sqlite", &connection);

    // Print connection state
    std::cout << "Database connection opened: "
              << connection->isOpen()
              << std::endl;

    if(!connection->isOpen()) {
        return;
    }

    std::cout << "Database connection string: "
              << connection->connectionString()
              << std::endl;


    // Create the SQL command
    Command::Ptr command;
    connection->createCommand("SELECT "
                              "clientId, firstName, lastName, "
                              "note1, note2, note3, note4 "
                              "FROM clients",
                              &command);

    // Execute the command and get SQL cursor
    Cursor::Ptr cursor;
    command->execute(&cursor);

    // Iterate the cursor
    while(cursor->next()) {
        int clientId;
        std::string firstName;
        std::string lastName;

        std::string note1;
        std::string note2;
        std::string note3;
        std::string note4;

        cursor->getValue(0, &clientId);
        cursor->getValue(1, &firstName);
        cursor->getValue(2, &lastName);
        cursor->getValue(3, &note1);
        cursor->getValue(4, &note2);
        cursor->getValue(5, &note3);
        cursor->getValue(6, &note4);

        std::cout << "id: " << clientId
                  << ", firstName: " << firstName
                  << ", lastName: " << lastName
                  << ", note1: " << note1
                  << ", note2: " << note2
                  << ", note3: " << note3
                  << ", note4: " << note4
                  << std::endl;
    }

    // Optionally close the connection (the connection may still be pooled)
    connection->close();
}

void testMapping() {
    // Obtain defaul connection pool instance
    ConnectionPool::Ptr connectionPool = ConnectionPool::instance();

    // Get database connection from the connection pool
    Connection::Ptr connection;
    connectionPool->connect("clients.sqlite", &connection);

    // Print connection state
    std::cout << "Database connection opened: "
              << connection->isOpen()
              << std::endl;

    if(!connection->isOpen()) {
        return;
    }

    std::cout << "Database connection string: "
              << connection->connectionString()
              << std::endl;


    // Create the SQL command
    Command::Ptr command;
    connection->createCommand("SELECT "
                              "clientId, firstName, lastName, "
                              "note1, note2, note3, note4 "
                              "FROM clients",
                              &command);

    // Execute the command and get SQL cursor
    Cursor::Ptr cursor;
    command->execute(&cursor);

    MappingSequence mapping(sequence_1);

    ObjectReader reader(mapping, cursor);
    std::cout << "Preparing to read customers..." << std::endl;
    while(cursor->next()) {
        Customer value;
        if(reader(&value) != 0) {
            std::cout << "Failed to read." << std::endl;
            break;
        } else {
            std::cout << "Read customer:" << std::endl;
            std::cout << value << std::endl;
        }
        reader.reset();
    }

    std::cout << "Done reading customers" << std::endl;
}

int main()
{
    testDatabase();
    testMapping();
    return 0;
}

