#include <iostream>
#include "typetraits.h"
#include "objectbuffer.h"

#include "account.h"
#include "customer.h"

#include "sqlcursor.h"

#include "mappingitem.h"
#include "mappingsequence.h"

#include "cursorreader.h"


// Generated table
const MappingItem sequence_1[] ={
    {7},
    {Customer::F_ID},
    {Customer::F_FIRST_NAME},
    {Customer::F_LAST_NAME},
    {Customer::F_AGE},
    {Customer::F_DATE_JOINED},
    {Customer::F_ACCOUNT_PRIMARY},

    {6},
    {Account::F_ACCOUNT_NAME},
    {Account::F_ACCOUNT_ID},
    {Account::F_ACCOUNT_TYPE},
    {Account::F_ACCOUNT_AMOUNT},
    {Account::F_ACCOUNT_DATE_OPENED},
    {Account::F_ACCOUNT_ACTIVE},

    {Customer::F_ACCOUNT_SECONDARY},

    {6},
    {Account::F_ACCOUNT_NAME},
    {Account::F_ACCOUNT_ID},
    {Account::F_ACCOUNT_TYPE},
    {Account::F_ACCOUNT_AMOUNT},
    {Account::F_ACCOUNT_DATE_OPENED},
    {Account::F_ACCOUNT_ACTIVE}
};

int main()
{
    MappingSequence mapping(sequence_1,
                            sizeof(sequence_1)/sizeof(sequence_1[0]));

    Customer customer;
    SqlCursor cursor;
    CursorReader reader(mapping, &cursor);
    reader(customer);

    return 0;
}

