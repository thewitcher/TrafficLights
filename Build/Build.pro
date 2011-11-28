#-------------------------------------------------
#
# Project created by QtCreator 2011-11-05T21:26:40
#
#-------------------------------------------------

QT       += core gui declarative

TARGET = application
TEMPLATE = app

SOURCES += main.cpp

win32:debug {
    LIBS += -L../Logic/debug/ -lLogic \
            -L../Ui/debug/ -lUi \
            -L../Logger/debug/ -lLogger \
            -L../Settings/debug/ -lSettings
}

win32:release {
    LIBS += -L../Logic/release/ -lLogic \
            -L../Ui/release/ -lUi \
            -L../Logger/release/ -lLogger \
            -L../Settings/release/ -lSettings
}

unix {
    LIBS += -L../Logic/ -lLogic \
            -L../Ui/ -lUi \
            -L../Logger/ -lLogger \
            -L../Settings/ -lSettings
}

