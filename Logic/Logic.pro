#-------------------------------------------------
#
# Project created by QtCreator 2011-11-05T21:24:46
#
#-------------------------------------------------

include(../Common.pri)
include(Algorithm/GA/GA.pri)
include(Algorithm/Custom/CustomGA.pri)

win32:debug {
    LIBS += -L../Settings/debug/ -lSettings
    LIBS += -L../Ui/debug/ -lUi
}

win32:release {
    LIBS += -L../Settings/release/ -lSettings
    LIBS += -L../Ui/debug/ -lUi
}
