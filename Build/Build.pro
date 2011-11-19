#-------------------------------------------------
#
# Project created by QtCreator 2011-11-05T21:26:40
#
#-------------------------------------------------

QT       += core gui

TARGET = application
TEMPLATE = app

SOURCES += main.cpp

LIBS += -L../Logic/ -lLogic \
        -L../Ui/ -lUi \
        -L../Logger/ -lLogger \
        -L../Settings/ -lSettings

INCLUDEPATH += ../Logic \
               ../Ui \
               ../Logger \
               ../Settings

DEPENDPATH += ../Logic \
              ../Ui \
              ../Logger \
              ../Settings


