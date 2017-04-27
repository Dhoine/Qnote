#-------------------------------------------------
#
# Project created by QtCreator 2016-11-22T10:01:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qnote
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    textedit.cpp \
    highlighter.cpp \
    reader.cpp \
    settingsform.cpp \
    settingsstorage.cpp

HEADERS  += mainwindow.h \
    textedit.h \
    highlighter.h \
    reader.h \
    settingsform.h \
    settingsstorage.h

FORMS    += mainwindow.ui \
    settingsform.ui

QMAKE_LFLAGS_RELEASE += -static -static-libgcc

RESOURCES +=

DISTFILES += \
    settings.xml \
    C,C++.xml

