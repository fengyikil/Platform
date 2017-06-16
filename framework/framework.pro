#-------------------------------------------------
#
# Project created by QtCreator 2017-06-12T11:43:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network
CONFIG +=console
TARGET = framework
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

INCLUDEPATH +=$$PWD/gui
INCLUDEPATH +=$$PWD/communication
INCLUDEPATH +=$$PWD/lib/lua/lua-5.3.4/src
INCLUDEPATH +=$$PWD/lua-extend
LIBS += -L$$PWD/lib/lua/ -llua53s

SOURCES += main.cpp\
    gui/mainwindow.cpp \
    communication/bytefifo.cpp \
    communication/communication.cpp \
    log/nsplog.cpp \
    ftest.cpp \
    fkmanage.cpp \
    lua-extend/lua_communication.cpp \
    communication/machine.cpp \
    lua-extend/lua_test.cpp

HEADERS  += \ 
    gui/mainwindow.h \
    communication/bytefifo.h \
    communication/communication.h \
    nsplog.h \
    log/nsplog.h \
    ftest.h \
    fkmanage.h \
    communication/machine.h

FORMS    += \
    gui/mainwindow.ui
