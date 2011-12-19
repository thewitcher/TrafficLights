#-------------------------------------------------
#
# Project created by QtCreator 2011-11-05T21:20:40
#
#-------------------------------------------------

include(../Common.pri)
include(Root_window/Root-window.pri)
include(QSSEngine/QSSEngine.pri)
include(Cars/Cars.pri)
include(Qml/Qml.pri)
include(Checkpoints_manager/Checkpoints_manager.pri)

RESOURCES += \
    graphics.qrc

# If You want to do something on the beginning just add some code to init.sh script
callScript.target = all

# Not checked (remember to edit init_windows.sh file)
win32:debug {
    callScript.commands = $${PWD}/Data/init_windows.sh $${PWD}/Data $${OUT_PWD}/../Build/Data
}

# Not checked (remember to edit init_windows.sh file)
win32:release {
    callScript.commands = $${PWD}/Data/init_windows.sh $${PWD}/Data $${OUT_PWD}/../Build/Data
}

unix {
    callScript.commands = $${PWD}/Data/init_linux.sh $${PWD}/Data $${OUT_PWD}/../Build/Data
}

QMAKE_EXTRA_TARGETS += callScript

