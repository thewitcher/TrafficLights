#-------------------------------------------------
#
# Project created by QtCreator 2011-11-05T21:26:40
#
#-------------------------------------------------

QT       += core gui declarative

TARGET = application
TEMPLATE = app

SOURCES += main.cpp

win32 {
    SOURCE_FILE=$${IN_PWD}/Data/init_windows.bat
    SOURCE_PATH=$${IN_PWD}/Data
    TARGET_PATH=$${OUT_PWD}/../Build/Data

    system($${replace(SOURCE_FILE,/,\\)} $${replace(SOURCE_PATH,/,\\)} $${replace(TARGET_PATH,/,\\)})
}

unix {
    SOURCE_FILE=$${IN_PWD}/Data/init_linux.sh
    SOURCE_PATH=$${IN_PWD}/Data
    TARGET_PATH=$${OUT_PWD}/../Build/Data

    system($${SOURCE_FILE} $${SOURCE_PATH} $${TARGET_PATH})
}

RESOURCES += \
    ../Ui/graphics.qrc

DEFINES += LOGGER

include(../Logger/Logger.pri)
include(../Logic/Logic.pri)
include(../Ui/Ui.pri)
include(../Settings/Settings.pri)
