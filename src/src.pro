QT += sql
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt



SOURCES += main.cpp \
    serverapp.cpp

HEADERS += \
    serverapp.h





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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../zhttp/release/ -lzhttp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../zhttp/debug/ -lzhttp
else:unix: LIBS += -L$$OUT_PWD/../zhttp/ -lzhttp

INCLUDEPATH += $$PWD/../zhttp
DEPENDPATH += $$PWD/../zhttp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zhttp/release/libzhttp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zhttp/debug/libzhttp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zhttp/release/zhttp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zhttp/debug/zhttp.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../zhttp/libzhttp.a

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../zworker/release/ -lzworker
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../zworker/debug/ -lzworker
else:unix: LIBS += -L$$OUT_PWD/../zworker/ -lzworker

INCLUDEPATH += $$PWD/../zworker
DEPENDPATH += $$PWD/../zworker

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zworker/release/libzworker.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zworker/debug/libzworker.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zworker/release/zworker.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zworker/debug/zworker.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../zworker/libzworker.a


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../karaokemanager/release/ -lkaraokemanager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../karaokemanager/debug/ -lkaraokemanager
else:unix: LIBS += -L$$OUT_PWD/../karaokemanager/ -lkaraokemanager

INCLUDEPATH += $$PWD/../karaokemanager
DEPENDPATH += $$PWD/../karaokemanager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../karaokemanager/release/libkaraokemanager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../karaokemanager/debug/libkaraokemanager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../karaokemanager/release/karaokemanager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../karaokemanager/debug/karaokemanager.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../karaokemanager/libkaraokemanager.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../adminmanager/release/ -ladminmanager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../adminmanager/debug/ -ladminmanager
else:unix: LIBS += -L$$OUT_PWD/../adminmanager/ -ladminmanager

INCLUDEPATH += $$PWD/../adminmanager
DEPENDPATH += $$PWD/../adminmanager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../adminmanager/release/libadminmanager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../adminmanager/debug/libadminmanager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../adminmanager/release/adminmanager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../adminmanager/debug/adminmanager.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../adminmanager/libadminmanager.a

INCLUDEPATH += /usr/local/include
LIBS += -L"/usr/local/lib" -lPocoFoundationd -lPocoJSONd -lPocoNetd -lPocoUtild -lPocoXMLd -lPocoNetSSLd
LIBS += -L"/usr/local/lib" -lPocoFoundation -lPocoJSON -lPocoNet -lPocoUtil -lPocoXML -lPocoNetSSLd
