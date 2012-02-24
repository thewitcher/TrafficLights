import QtQuick 1.0
import Cars 1.0

MotorCar {
    id:root

    width: 20
    height: 20

    property alias realWidth: rootRect.realWidth
    property alias realHeight: rootRect.realHeight

    property alias bumperX: collisionPoint.x
    property alias bumperY: collisionPoint.y

    property string imageSource: "qrc:/graphics/Graphics/motor_car_small_bright.png"

    Item {
        id: collisionPoint
        width: 1; height: 1
        x:-10; y:9 // If You want to increase space between vehicles, just set x less value.
    }

function onBackLights()
{
    rootRect.state = "stop"
}

function offBackLights()
{
    rootRect.state = "go"
}

function turnOnLeftBlinkers()
{
    leftBlinkers.running = true
}

function turnOnRightBlinkers()
{
    rightBlinkers.running = true
}

function stopBlinkers()
{
    rightBlinkers.running = false
    rightTurnSignal.scale = 1
    leftBlinkers.running = false
    leftTurnSignal.scale = 1
}

function turnOnLongLights()
{
    longLeftLight.state = "night"
    longRightLight.state = "night"
}

function turnOffLongLights()
{
    longLeftLight.state = "day"
    longRightLight.state = "day"
}

    Item {
        id:rootRect
        width: 20
        height: 20
        rotation: -90

        property int realWidth: auto.width
        property int realHeight: auto.height
        property int insideTime: 0

        SequentialAnimation {
            id: leftBlinkers
            running: false
            loops: Animation.Infinite
            PropertyAnimation { target: leftTurnSignal; property: "scale";
                                to: 5 ; duration: 250 }
            PropertyAnimation { target: leftTurnSignal; property: "scale";
                                to: 1 ; duration: 250 }


        }
        SequentialAnimation {
            id: rightBlinkers
            running: false
            loops: Animation.Infinite
            PropertyAnimation { target: rightTurnSignal; property: "scale";
                                to: 5 ; duration: 250 }

            PropertyAnimation { target: rightTurnSignal; property: "scale";
                                to: 1 ; duration: 250 }
        }

        states:[
        State {
            name: "stop"
            PropertyChanges { target: backLeftLight; color: "#a80707"; scale: 1.5 }
            PropertyChanges { target: backRightLight; color: "#a80707"; scale: 1.5 }
        },
        State {
            name: "go"
            PropertyChanges { target: backLeftLight; color: "yellow"; scale: 1 }
            PropertyChanges { target: backRightLight; color: "yellow"; scale: 1 }
        }]

        state: "go"

        Blinkers{
            id:leftTurnSignal
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -7
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -7
        }

        Blinkers{
            id:rightTurnSignal
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -7
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 8.5
        }

        Image {
            id: auto
            anchors.centerIn: rootRect
            source: imageSource
        }

        BackLight{
            id: backLeftLight
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 12
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -5.5
        }

        BackLight{
            id: backRightLight
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 12
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 6.5
        }

        LongLight{
            id: longLeftLight
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -26
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -5
        }

        LongLight{
            id:longRightLight
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -26
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 6
        }
    }
}
