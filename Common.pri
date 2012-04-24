QT       += core gui declarative
TEMPLATE  = lib

win32:debug {
    LIBS += -L../Logger/debug -lLogger
#    LIBS += -L../Logic/debug -lLogic
}

win32:release {
    LIBS += -L../Logger/release -lLogger
#    LIBS += -L../Logic/release -lLogic
}

unix {
    LIBS += -L../Logger/ -lLogger
}
