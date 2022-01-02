
message(Including $$_FILE_ from $$IN_PWD)
INCLUDEPATH += $$IN_PWD

#PRE_TARGETDEPS += $$OUT_PWD/../groundupdb/groundupdb.lib

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../groundupdb/release/libgroundupdb.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../groundupdb/debug/libgroundupdb.a
