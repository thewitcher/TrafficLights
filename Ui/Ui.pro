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
include(TrafficLights_manager/TrafficLights_manager.pri)
include(Lights/Lights.pri)
include(Checkpoints_manager/Checkpoints_manager.pri)

RESOURCES += \
    graphics.qrc

# Calls init script

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

