import QtQuick 1.0
import Cars 1.0

MotorCar {
    id:root

    width: 18
    height: 18
    //scale:3

    property alias bumperX: collisionPoint.x
    property alias bumperY: collisionPoint.y

signal turnOnLongLights

    onTurnOnLongLights: {
    longLeftLight.state = "night"
    longRightLight.state = "night"
}

function turnOnSignal()
{
    timer.running = true
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
    leftBlinkers.running = false
}

function turnOnLongLight()
{
    longLeftLight.state = "night"
    longRightLight.state = "night"
}

    Item {
        id:rootRect
        width: 18
        height: 18
        rotation: -90

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

        transitions: [
            Transition {
                from: "go"
                to: "stop"
                PropertyAnimation{
                    targets:[ backLeftLight, backRightLight, stopLight ]
                    properties: "color,scale,opacity"; duration: 1200
                }
            },
            Transition {
                from: "stop"
                to: "go"
                PropertyAnimation{
                    targets:[ backLeftLight, backRightLight, stopLight ]
                    properties: "color,scale"
                }
            }
        ]

        state: "go"

        Blinkers{
            id:leftTurnSignal
            x:5.6 ; y: 6
        }

        Blinkers{
            id:rightTurnSignal
            x:11.1; y:6
        }

        Image {
            id: auto
            anchors.centerIn: rootRect
            source: "qrc:/graphics/Graphics/motor_car.png"
            scale:0.15
        }

        BackLight{
            id: backLeftLight
            x:6; y:14
        }

        BackLight{
            id: backRightLight
            x:11; y:14
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

        Rectangle{
            id: collisionPoint
            width: 1; height: 1
            color: "yellow"
            x:8.5; y:-11
        }
    }
}
