QT += core
QT -= gui

CONFIG += c++11

TARGET = konstpro
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    site.cpp \
    homepage.cpp \
    content.cpp \
    cvpage.cpp

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
    homePage.html \
    briefCv.xhtml
