CONFIG -= qt

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/database.cpp \
    src/groundupdb.cpp

HEADERS += \
    include/database.h \
    include/extensions/extdatabase.h \
    include/groundupdb.h \
    groundupdb.h

INCLUDEPATH += include

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    defines.pri
