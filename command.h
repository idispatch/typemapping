#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include "cursor.h"
#include "datetime.h"
#include "datetimetz.h"

//TODO: Command Flags
//TODO: Transient binding

class Command {
public:
    typedef std::shared_ptr<Command> Ptr;

    virtual ~Command();

    virtual bool bindNull(int index) = 0;

    virtual bool bind(int index,          bool value) = 0;

    virtual bool bind(int index,          char value) = 0;
    virtual bool bind(int index, signed   char value) = 0;
    virtual bool bind(int index, unsigned char value) = 0;

    virtual bool bind(int index, signed   short int value) = 0;
    virtual bool bind(int index, unsigned short int value) = 0;

    virtual bool bind(int index, signed   int value) = 0;
    virtual bool bind(int index, unsigned int value) = 0;

    virtual bool bind(int index, signed   long long value) = 0;
    virtual bool bind(int index, unsigned long long value) = 0;

    virtual bool bind(int index, float value) = 0;
    virtual bool bind(int index, double value) = 0;

    virtual bool bind(int index, const std::string& value) = 0;
    virtual bool bind(int index, const std::vector<char>& value) = 0;

    virtual bool bind(int index, const Datetime& value) = 0;
    virtual bool bind(int index, const DatetimeTz& value) = 0;

    virtual bool reset() = 0;

    virtual bool execute(const char *query, Cursor::Ptr *cursor) = 0;

    virtual bool execute(Cursor::Ptr *cursor) = 0;
};

#endif // COMMAND_H
