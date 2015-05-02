#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H

#include "typetraits.h"

class AccountType {
public:
    enum Value {
        CHECKING = 0,
        SAVINGS = 1
    };

    static int toInt(AccountType::Value value) {
        return value;
    }
};

template<>
struct IsEnum<AccountType::Value> : TrueType {
    typedef AccountType Wrapper;
};

#endif // ACCOUNTTYPE_H
