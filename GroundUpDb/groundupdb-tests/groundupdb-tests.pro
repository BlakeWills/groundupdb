TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        dbmanagement-tests.cpp \
        main.cpp

include(../groundupdb/Defines.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../groundupdb/release -lgroundupdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../groundupdb/debug -lgroundupdb

HEADERS += \
    catch.hpp \
    tests.h
