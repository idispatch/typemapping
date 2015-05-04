#ifndef SQLCOMMAND_H
#define SQLCOMMAND_H

#include "command.h"
#include <sqlite3.h>

//TODO: Transient binding

class SqlCommand : public Command {
    friend class SqlConnection;

    sqlite3      *d_dbHandle;  // Held, not owned
    sqlite3_stmt *d_statement; // Owned

    SqlCommand(sqlite3      *dbHandle);
    SqlCommand(sqlite3_stmt *statement);

    void closeCommand();
public:
    ~SqlCommand();

    bool numColumns(int *result);

    bool bindNull(int index);

    bool bind(int index,          bool value);

    bool bind(int index,          char value);
    bool bind(int index, signed   char value);
    bool bind(int index, unsigned char value);

    bool bind(int index, signed   short int value);
    bool bind(int index, unsigned short int value);

    bool bind(int index, signed   int value);
    bool bind(int index, unsigned int value);

    bool bind(int index, signed   long long value);
    bool bind(int index, unsigned long long value);

    bool bind(int index, float value);
    bool bind(int index, double value);

    bool bind(int index, const std::string& value);
    bool bind(int index, const std::vector<char>& value);

    bool bind(int index, const Datetime& value);
    bool bind(int index, const DatetimeTz& value);

    bool reset();

    bool execute(const char *query, Cursor::Ptr *cursor);

    bool execute(Cursor::Ptr *cursor);
};

#endif // SQLCOMMAND_H
