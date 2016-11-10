#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T10:01:15
#
#-------------------------------------------------

QT       -= core gui

TARGET = zhttp
TEMPLATE = lib
CONFIG += staticlib

unix {
    target.path = /usr/lib
    INSTALLS += target
}


HEADERS += \
    src/zhttp/http.h \
    private/httprequesthandlerfactory.h \
    private/timerequesthandler.h \
    private/versionrequesthandler.h \
    src/zhttp/httprequestbasehandler.h \
    private/httpkaraokerequesthandler.h \
    private/httpclient.h \
    private/httpadminrequesthandler.h \
    private/httpuserrequesthandler.h \
    private/httpsclient.h

SOURCES += \
    src/zhttp/http.cpp \
    private/timerequesthandler.cpp \
    private/versionrequesthandler.cpp \
    private/httprequesthandlerfactory.cpp \
    src/zhttp/httprequestbasehandler.cpp \
    private/httpkaraokerequesthandler.cpp \
    private/httpclient.cpp \
    private/httpadminrequesthandler.cpp \
    private/httpuserrequesthandler.cpp \
    private/httpsclient.cpp


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


INCLUDEPATH += /usr/local/include
LIBS += -L"/usr/local/lib" -lPocoFoundationd -lPocoJSONd -lPocoNetd -lPocoUtild -lPocoXMLd -lPocoNetSSLd
LIBS += -L"/usr/local/lib" -lPocoFoundation -lPocoJSON -lPocoNet -lPocoUtil -lPocoXML -lPocoNetSSLd
