#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T19:01:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Example
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    SMSystem.cpp

HEADERS  += mainwindow.h \
    SMSystem.h

FORMS    += mainwindow.ui

LIBS    += -lsmsystem
