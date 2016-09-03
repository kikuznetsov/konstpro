QT += core
QT -= gui

CONFIG += c++11

TARGET = konstpro
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

#copy xhtml-files to build directory
copyfiles.commands += @echo COPY FROM $${PWD} TO $${OUT_PWD} &
copyfiles.commands += cp -r $${PWD}/briefCv.xhtml $${OUT_PWD}/ &
copyfiles.commands += cp -r $${PWD}/homePage.xhtml $${OUT_PWD}/ &
copyfiles.commands += cp -r $${PWD}/header.xhtml $${OUT_PWD}/ &
#copyfiles.commands += cp -r $${PWD}/$${DISTFILES} $${OUT_PWD}/$${DISTFILES} &
copyfiles.commands += echo Finished deployment

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

SOURCES += main.cpp \
    site.cpp \
    homepage.cpp \
    content.cpp \
    cvpage.cpp \
    loadproc.cpp

QMAKE_CXXFLAGS += -g
QMAKE_CXXFLAGS += -std=c++0x

LIBS += -L/usr/local/lib -lwthttp -lwt -lboost_regex -lboost_signals
LIBS += -lboost_system -lboost_thread -lboost_filesystem -lboost_date_time
LIBS += -lwtdbo -lwtdbosqlite3

HEADERS += \
    site.h \
    homepage.h \
    content.h \
    loadproc.h \
    cvpage.h

DISTFILES += \
    briefCv.xhtml \
    homePage.xhtml \
    header.xhtml


