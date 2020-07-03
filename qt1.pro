#-------------------------------------------------
#
# Project created by QtCreator 2020-06-11T16:15:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    zhuwin.cpp \
    model.cpp

HEADERS += \
        mainwindow.h \
    zhuwin.h \
    model.h

FORMS += \
        mainwindow.ui \
    zhuwin.ui

RESOURCES += \
    src.qrc

DISTFILES += \
    image/11.png \
    image/12.png \
    image/13.png \
    image/14.png \
    image/15.png \
    image/test.bmp
RC_FILE = logo.rc
