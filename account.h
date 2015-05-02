#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "typetraits.h"
#include "accounttype.h"
#include "datetimetz.h"

class Account {
    int                 d_id;
    std::string         d_name;
    AccountType::Value  d_accountType;
    double              d_amount;
    bool                d_active;
    DatetimeTz          d_dateOpened;
public:
    enum {
        F_ACCOUNT_NAME = 0,
        F_ACCOUNT_ID = 1,
        F_ACCOUNT_TYPE = 2,
        F_ACCOUNT_AMOUNT = 4,
        F_ACCOUNT_ACTIVE = 5,
        F_ACCOUNT_DATE_OPENED = 6
    };
    Account(int id,
            std::string const &name,
            AccountType::Value accountType)
        : d_id(id),
          d_name(name),
          d_accountType(accountType),
          d_amount(0.0),
          d_active(true)
    {}

    template<typename MANIPULATOR>
    int manipulate(MANIPULATOR& manipulator, int id) {
        switch(id) {
        case F_ACCOUNT_NAME:
            return manipulator(d_name);
        case F_ACCOUNT_ID:
            return manipulator(d_id);
        case F_ACCOUNT_TYPE:
            return manipulator(d_accountType);
        case F_ACCOUNT_ACTIVE:
            return manipulator(d_active);
        case F_ACCOUNT_AMOUNT:
            return manipulator(d_amount);
        case F_ACCOUNT_DATE_OPENED:
            return manipulator(d_dateOpened);
        default:
            return -1;
        }
    }
};

template<>
struct IsSequence<Account> : TrueType {};

#endif // ACCOUNT_H
