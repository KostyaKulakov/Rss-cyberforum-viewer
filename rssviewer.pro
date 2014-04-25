#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T18:05:40
#
#-------------------------------------------------

QT       += core gui xml network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rssviewer
TEMPLATE = app

INCLUDEPATH += src/ ui/ include/

SOURCES += src/main.cpp\
    src/xmlparser.cpp \
    src/mainwindow.cpp \
    src/wabout.cpp \
    src/wsetting.cpp \
    src/settings.cpp

HEADERS  += \
    include/xmlparser.h \
    include/mainwindow.h \
    include/wabout.h \
    include/wsetting.h \
    include/settings.h

FORMS    += \
    ui/mainwindow.ui \
    ui/wabout.ui \
    ui/wsetting.ui

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    resource/myapp.rc

RESOURCES += \
    resource/res.qrc

RC_FILE = resource/myapp.rc
