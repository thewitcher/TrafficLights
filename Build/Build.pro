#-------------------------------------------------
#
# Project created by QtCreator 2011-11-05T21:26:40
#
#-------------------------------------------------

QT       += core gui declarative

TARGET = application
TEMPLATE = app

SOURCES += main.cpp

RESOURCES += \
    ../Ui/graphics.qrc


# You can define:
# LOGGER - to have trace
# COLLISIONS - to turn on collisions detection
# LIGHTS - to turn on light in vehicle
# EVENTS - to turn on timer which manages global events like day and night for example
#DEFINES += COLLISIONS \
#           LOGGER \
#           LIGHTS \
#           EVENTS


include(../Logger/Logger.pri)
include(../Logic/Logic.pri)
include(../Ui/Ui.pri)
include(../Settings/Settings.pri)
