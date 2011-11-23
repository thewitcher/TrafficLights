QT       += core gui
TEMPLATE  = lib

win32:debug {
    LIBS += -L../Logger/debug/ -lLogger
}

win32:release {
    LIBS += -L../Logger/release/ -lLogger
}

unix {
    LIBS += -L../Logger/ -lLogger
}
