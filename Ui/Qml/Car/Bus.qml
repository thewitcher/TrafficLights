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

    Item {
        id: collisionPoint
        width: 1; height: 1
        x:-25; y:9 // If You want to increase space between vehicles, just set x less value.
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
        anchors.centerIn: root
        rotation: -90

        property int realWidth: auto.width
        property int realHeight: auto.height

        SequentialAnimation {
            id: leftBlinkers
            running: false
            loops: Animation.Infinite
            PropertyAnimation { target: leftTurnSignal; property: "scale";
                                to:3 ; duration: 250 }
            PropertyAnimation { target: leftTurnSignal; property: "scale";
                                to: 1 ; duration: 250 }
        }
        SequentialAnimation {
            id: rightBlinkers
            running: false
            loops: Animation.Infinite
            PropertyAnimation { target: rightTurnSignal; property: "scale";
                                to:3 ; duration: 250 }
            PropertyAnimation { target: rightTurnSignal; property: "scale";
                                to: 1 ; duration: 250 }
        }

        states:[
        State {
            name: "stop"
            PropertyChanges { target: backLeftLight; opacity: 1 }
            PropertyChanges { target: backRightLight; opacity: 1 }
            PropertyChanges { target: secondBackLeftLight; opacity: 0 }
            PropertyChanges { target: secondBackRightLight; opacity: 0 }
        },
        State {
            name: "go"
            PropertyChanges { target: backLeftLight; opacity: 0 }
            PropertyChanges { target: backRightLight; opacity: 0 }
            PropertyChanges { target: secondBackLeftLight; opacity: 0 }
            PropertyChanges { target: secondBackRightLight; opacity: 0 }
        }]

        state: "go"

        Blinkers{
            id:leftTurnSignal
            scale: 10
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -51
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -100
        }

        Blinkers{
            id:rightTurnSignal
            scale: 10
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 53
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -100
        }

        Image {
            id: auto
            anchors.centerIn: rootRect
            source: "qrc:/graphics/Graphics/bus4_small.png"
        }

        BackLight{
            id: backLeftLight
            scale: 10
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -40
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 185
        }

        BackLight{
            id: secondBackLeftLight
            scale: 10
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -25
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 188
        }

        BackLight{
            id: backRightLight
            scale: 10
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 40
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 185
        }

        BackLight{
            id: secondBackRightLight
            scale: 10
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 25
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 188
        }

        LongLight{
            id: longLeftLight
            rotation: 180
            scale: 2
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 35
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -250
        }

        LongLight{
            id:longRightLight
            rotation: 180
            scale: 2
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -35
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -250
        }
    }
}
