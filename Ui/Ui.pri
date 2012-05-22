# Root-window
SOURCES += ../Ui/Root_window/root-window.cpp \
           ../Ui/Root_window/graphics-view.cpp \
           ../Ui/Root_window/qml-helper.cpp \
           ../Ui/Root_window/graphics-scene.cpp \
           ../Ui/Root_window/event-timer.cpp \
    ../Ui/Choose_algorithm_type_and_parameters/choose-algorithm-type.cpp

HEADERS += ../Ui/Root_window/root-window.h \
           ../Ui/Root_window/graphics-view.h \
           ../Ui/Root_window/qml-helper.h \
           ../Ui/Root_window/graphics-scene.h \
           ../Ui/Root_window/event-timer.h \
    ../Ui/Choose_algorithm_type_and_parameters/choose-algorithm-type.h

FORMS   += ../Ui/Root_window/root-window.ui \
    ../Ui/Choose_algorithm_type_and_parameters/choose-algorithm-type.ui

# Cars
SOURCES += \
    ../Ui/Cars/vehicle.cpp \
    ../Ui/Cars/sequential-move.cpp \
    ../Ui/Cars/parallel-move.cpp \
    ../Ui/Cars/property-move.cpp \
    ../Ui/Cars/simple-move.cpp \
    ../Ui/Cars/motor-car.cpp \
    ../Ui/Cars/collision-point.cpp \
    ../Ui/Cars/bus-car.cpp

HEADERS += \
    ../Ui/Cars/vehicle.h \
    ../Ui/Cars/sequential-move.h \
    ../Ui/Cars/parallel-move.h \
    ../Ui/Cars/property-move.h \
    ../Ui/Cars/simple-move.h \
    ../Ui/Cars/motor-car.h \
    ../Ui/Cars/collision-point.h \
    ../Ui/Cars/bus-car.h

# Qml
OTHER_FILES += \
    ../Ui/Qml/Car/BackLight.qml \
    ../Ui/Qml/Car/LongLight.qml \
    ../Ui/Qml/Car/Blinkers.qml \
    ../Ui/Qml/Car/MotorCar.qml \
    ../Ui/Qml/Lights/Lights.qml \
    ../Ui/Qml/Lights/ArrowInLeft.qml \
    ../Ui/Qml/Lights/ArrowInRight.qml \
    ../Ui/Qml/Lights/ArrowStraight.qml \
    ../Ui/Qml/Lights/ArrowStraightAndLeft.qml \
    ../Ui/Qml/Lights/ArrowStraightAndRight.qml \
    ../Ui/Qml/Car/Bus.qml

# TrafficLights
HEADERS += \
    ../Ui/TrafficLights_manager/deploy-trafficlights.h \
    ../Ui/TrafficLights_manager/junction-manager.h \
    ../Ui/TrafficLights_manager/junction.h \
    ../Ui/TrafficLights_manager/simple-junction.h \
    ../Ui/TrafficLights_manager/bladzio-junction.h \
    ../Ui/TrafficLights_manager/vehicle-count-manager.h \
    ../Ui/TrafficLights_manager/constans.h

SOURCES += \
    ../Ui/TrafficLights_manager/deploy-trafficlights.cpp \
    ../Ui/TrafficLights_manager/junction-manager.cpp \
    ../Ui/TrafficLights_manager/junction.cpp \
    ../Ui/TrafficLights_manager/simple-junction.cpp \
    ../Ui/TrafficLights_manager/bladzio-junction.cpp \
    ../Ui/TrafficLights_manager/vehicle-count-manager.cpp \
    ../Ui/TrafficLights_manager/constans.cpp

# Lights
SOURCES += \
    ../Ui/Lights/trafficlight.cpp

HEADERS += \
    ../Ui/Lights/trafficlight.h

# CheckpointManager
HEADERS += \
    ../Ui/Checkpoints_manager/checkpoint.h \
    ../Ui/Checkpoints_manager/path.h \
    ../Ui/Checkpoints_manager/checkpoint-manager.h \
    ../Ui/Checkpoints_manager/checkpoint-creator.h

SOURCES += \
    ../Ui/Checkpoints_manager/checkpoint.cpp \
    ../Ui/Checkpoints_manager/path.cpp \
    ../Ui/Checkpoints_manager/checkpoint-manager.cpp \
    ../Ui/Checkpoints_manager/checkpoint-creator.cpp



