#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "typetraits.h"
#include "nullable.h"
#include "datetime.h"
#include "account.h"

class Customer {
    int             d_id;
    std::string     d_firstName;
    std::string     d_lastName;

    Nullable<int>   d_age;
    Datetime        d_dateJoined;

    Account         d_acc1;
    Account         d_acc2;

    std::vector<std::string>     d_notes;
public:
    enum {
        F_FIRST_NAME = 0,
        F_LAST_NAME = 4,
        F_AGE = 30,
        F_DATE_JOINED = 31,
        F_ID = 1,
        F_ACCOUNT_PRIMARY = 2,
        F_ACCOUNT_SECONDARY = 3,
        F_NOTES = 70
    };
    Customer()
        : d_id(42),
          d_firstName("John"),
          d_lastName("Doe"),
          d_age(50),
          d_acc1(5,"chequing",AccountType::CHEQUING),
          d_acc2(6,"savings",AccountType::SAVINGS)
    {}

    int id() const {
        return d_id;
    }

    const std::string& firstName() const {
        return d_firstName;
    }

    const std::string& lastName() const {
        return d_lastName;
    }

    const std::vector<std::string>& notes() const {
        return d_notes;
    }

    template<typename MANIPULATOR>
    int manipulate(MANIPULATOR& manipulator, int id) {
        switch(id) {
        case F_FIRST_NAME:
            return manipulator(&d_firstName);
        case F_LAST_NAME:
            return manipulator(&d_lastName);
        case F_ID:
            return manipulator(&d_id);
        case F_ACCOUNT_PRIMARY:
            return manipulator(&d_acc1);
        case F_ACCOUNT_SECONDARY:
            return manipulator(&d_acc2);
        case F_AGE:
            return manipulator(&d_age);
        case F_DATE_JOINED:
            return manipulator(&d_dateJoined);
        case F_NOTES:
            return manipulator(&d_notes);
        default:
            return -1;
        }
    }
};

template<>
struct IsSequence<Customer> : TrueType {};


inline
std::ostream& operator <<  (std::ostream& stream, const Customer& value) {
    stream << "[" << " id: " << value.id()
                  << " firstName: " << value.firstName()
                  << " lastName: " << value.lastName();
    const std::vector<std::string>& notes = value.notes();
    const std::size_t numNotes = notes.size();
    for(std::size_t i = 0; i < numNotes; ++i) {
        stream << " note" << i+1 << ": " << notes[i];
    }
    stream << "]";
    return stream;
}


#endif // CUSTOMER_H
