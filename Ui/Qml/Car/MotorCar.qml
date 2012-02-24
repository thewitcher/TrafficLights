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
            PropertyChanges { target: backLeftLight; color: "#a80707"; scale: 2 }
            PropertyChanges { target: backRightLight; color: "#a80707"; scale: 2 }
            PropertyChanges { target: stopLight; opacity:1}
        },
        State {
            name: "go"
            PropertyChanges { target: backLeftLight; color: "yellow"; scale:1 }
            PropertyChanges { target: backRightLight; color: "yellow"; scale:1 }
            PropertyChanges { target: stopLight; opacity:0 }
        }]

        state: "go"

        Blinkers{
            id:leftTurnSignal
            x:5.6 ; y: 6
        }

        Blinkers{
            id:rightTurnSignal
            x:11; y:6
        }

        Image {
            id: auto
            anchors.centerIn: rootRect
            source: imageSource
        }

        BackLight{
            id: backLeftLight
            x:5.5; y:14
        }

        BackLight{
            id: backRightLight
            x:11.5; y:14
        }

        Rectangle{
            id: stopLight
            x:8.85; y:13
            width: 0.3; height: 2
            radius: 6
            rotation: 90
            color: "#a80707"
            opacity: 0
        }

        LongLight{
            id: longLeftLight
            x:-3.1; y:-12.5
        }

        LongLight{
            id:longRightLight
            x:2.1; y:-12.5
        }
    }
}
