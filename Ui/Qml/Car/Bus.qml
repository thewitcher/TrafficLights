import QtQuick 1.0
import Cars 1.0

BusCar {
    id:root

    width: 20
    height: 20

    property alias realWidth: rootRect.realWidth
    property alias realHeight: rootRect.realHeight

    property alias bumperX: collisionPoint.x
    property alias bumperY: collisionPoint.y

    property string imageSource: "qrc:/graphics/Graphics/bus4_small_bright.png"

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
            PropertyChanges { target: backLeftLight; opacity: 1 }
            PropertyChanges { target: backRightLight; opacity: 1 }
            PropertyChanges { target: secondBackLeftLight; opacity: 1 }
            PropertyChanges { target: secondBackRightLight; opacity: 1 }
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
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -15
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -7
        }

        Blinkers{
            id:rightTurnSignal
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -15
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 8
        }

        Image {
            id: auto
            anchors.centerIn: rootRect
            source: imageSource
        }

        BackLight{
            id: backLeftLight
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 29
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -6
        }

        BackLight{
            id: secondBackLeftLight
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 27.5
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -1.5
        }

        BackLight{
            id: backRightLight
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 29
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 7
        }

        BackLight{
            id: secondBackRightLight
            color: "red"
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: 27.5
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 2
        }

        LongLight{
            id: longLeftLight
            rotation: -90
            scale: 0.6
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -47
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: -6
        }

        LongLight{
            id:longRightLight
            rotation: -90
            scale: 0.6
            anchors.verticalCenter: auto.verticalCenter
            anchors.verticalCenterOffset: -47
            anchors.horizontalCenter: auto.horizontalCenter
            anchors.horizontalCenterOffset: 6
        }
    }
}
