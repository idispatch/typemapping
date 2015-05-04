#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H

#include "typetraits.h"

class AccountType {
public:
    enum Value {
        CHEQUING = 0,
        SAVINGS = 1
    };

    static int toInt(AccountType::Value value) {
        return value;
    }

    static AccountType::Value fromInt(int value) {
        AccountType::Value result;
        switch(value) {
        case AccountType::CHEQUING:
        case AccountType::SAVINGS:
            result = static_cast<AccountType::Value>(value);
            break;
        }
        return result;
    }
};

template<>
struct IsEnum<AccountType::Value> : TrueType {
    typedef AccountType Wrapper;
};

#endif // ACCOUNTTYPE_H
