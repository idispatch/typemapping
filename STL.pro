TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

LIBS += -L/usr/local/Cellar/sqlite/3.8.9/lib -lsqlite3

SOURCES += main.cpp \
    indexedfieldset.cpp \
    cursor.cpp \
    indexedtypeset.cpp \
    connection.cpp \
    connectionpool.cpp \
    connectionfactory.cpp \
    sqlconnection.cpp \
    command.cpp \
    sqlcommand.cpp \
    sqlcursor.cpp

HEADERS += \
    cursor.h \
    typetraits.h \
    objectbuffer.h \
    nullable.h \
    datetime.h \
    accounttype.h \
    account.h \
    customer.h \
    connection.h \
    indexedfieldset.h \
    sqlcursor.h \
    indexedtypeset.h \
    fieldtype.h \
    mappingsequence.h \
    mappingitem.h \
    cursorreader.h \
    datetimetz.h \
    connectionpool.h \
    connectionfactory.h \
    sqlconnection.h \
    command.h \
    sqlcommand.h
