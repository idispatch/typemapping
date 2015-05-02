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
    {Customer::F_ID,                  0},
    {Customer::F_FIRST_NAME,          1},
    {Customer::F_LAST_NAME,           2},
    {Customer::F_AGE,                 3},
    {Customer::F_DATE_JOINED,         4},
    {Customer::F_ACCOUNT_PRIMARY,    -1},

    {6},
    {Account::F_ACCOUNT_NAME,         5},
    {Account::F_ACCOUNT_ID,           6},
    {Account::F_ACCOUNT_TYPE,         7},
    {Account::F_ACCOUNT_AMOUNT,       8},
    {Account::F_ACCOUNT_DATE_OPENED,  9},
    {Account::F_ACCOUNT_ACTIVE,      10},

    {Customer::F_ACCOUNT_SECONDARY,  -1},

    {6},
    {Account::F_ACCOUNT_NAME,        11},
    {Account::F_ACCOUNT_ID,          12},
    {Account::F_ACCOUNT_TYPE,        13},
    {Account::F_ACCOUNT_AMOUNT,      14},
    {Account::F_ACCOUNT_DATE_OPENED, 15},
    {Account::F_ACCOUNT_ACTIVE,      16}
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

