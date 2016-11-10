#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T09:22:07
#
#-------------------------------------------------

QT       -= core gui

TARGET = zworker
TEMPLATE = lib
CONFIG += staticlib

SOURCES += src/zworker/zworker.cpp

HEADERS += src/zworker/zworker.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../zcommon/release/ -lzcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../zcommon/debug/ -lzcommon
else:unix: LIBS += -L$$OUT_PWD/../zcommon/ -lzcommon

INCLUDEPATH += $$PWD/../zcommon
DEPENDPATH += $$PWD/../zcommon

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zcommon/release/libzcommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zcommon/debug/libzcommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zcommon/release/zcommon.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zcommon/debug/zcommon.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../zcommon/libzcommon.a


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../zsession/release/ -lzsession
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../zsession/debug/ -lzsession
else:unix: LIBS += -L$$OUT_PWD/../zsession/ -lzsession

INCLUDEPATH += $$PWD/../zsession
DEPENDPATH += $$PWD/../zsession

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zsession/release/libzsession.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zsession/debug/libzsession.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zsession/release/zsession.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zsession/debug/zsession.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../zsession/libzsession.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../zdb/release/ -lzdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../zdb/debug/ -lzdb
else:unix: LIBS += -L$$OUT_PWD/../zdb/ -lzdb

INCLUDEPATH += $$PWD/../zdb
DEPENDPATH += $$PWD/../zdb

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zdb/release/libzdb.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zdb/debug/libzdb.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zdb/release/zdb.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zdb/debug/zdb.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../zdb/libzdb.a


INCLUDEPATH += /usr/local/include
LIBS += -L"/usr/local/lib" -lPocoFoundationd -lPocoJSONd -lPocoNetd -lPocoUtild -lPocoXMLd
LIBS += -L"/usr/local/lib" -lPocoFoundation -lPocoJSON -lPocoNet -lPocoUtil -lPocoXML

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../usermanager/release/ -lusermanager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../usermanager/debug/ -lusermanager
else:unix: LIBS += -L$$OUT_PWD/../usermanager/ -lusermanager

INCLUDEPATH += $$PWD/../usermanager
DEPENDPATH += $$PWD/../usermanager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../usermanager/release/libusermanager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../usermanager/debug/libusermanager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../usermanager/release/usermanager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../usermanager/debug/usermanager.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../usermanager/libusermanager.a
