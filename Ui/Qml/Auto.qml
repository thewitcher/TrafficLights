import QtQuick 1.0
import Cars 1.0

MyCars{
id:root

    width: 18
    height: 18

    scale:3

signal turnOnLongLights
onTurnOnLongLights: {

    longLeftLight.state = "night"
    longRightLight.state = "night"
}

function turnOnSignal()
{
    timer.running = true
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
//        color: "blue"

        property int insideTime: 0

        Timer{
            id:timer
            interval: 500
            repeat: true
            running: false
            onTriggered: {
                rootRect.insideTime = rootRect.insideTime + 1
                if(root.m_turnSignal == MyCars.TurnRight)
                {
                    if(rootRect.insideTime % 2)
                    {
                        leftTurnSignal.color = "#be6e13"
                        rightTurnSignal.color = "#ff750b"
                        rightTurnSignal.scale = 2.5
                    }
                    else
                    {
                        rightTurnSignal.color = "#be6e13"
                        rightTurnSignal.scale = 1
                    }
                }
                else if(root.m_turnSignal == MyCars.TurnLeft){
                    if(rootRect.insideTime % 2)
                    {
                        rightTurnSignal.color = "#be6e13"
                        rightTurnSignal.scale = 1
                        leftTurnSignal.color = "#ff750b"
                        leftTurnSignal.scale = 2.5
                    }
                    else
                    {
                        leftTurnSignal.color = "#be6e13"
                        leftTurnSignal.scale = 1
                    }
                }
                else
                {
                    timer.running = false
                    rightTurnSignal.color = "#be6e13"
                    leftTurnSignal.color = "#be6e13"
                    rightTurnSignal.scale = 1
                    leftTurnSignal.scale = 1
                }

                if(rootRect.insideTime == 10)
                    rootRect.insideTime = 0
            }
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

        TurnSignal{
            id:leftTurnSignal
            x:5.6 ; y: 6
        }

        TurnSignal{
            id:rightTurnSignal
            x:11.1; y:6
        }

        Image {
            id: auto
            anchors.centerIn: rootRect
            source: "qrc:/graphics/Graphics/osobowe2.png"
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
        MouseArea{
            anchors.fill: auto
            onClicked: {
                if(parent.state == "go")
                    parent.state = "stop"
                else
                    parent.state = "go"

                rootRect.turnOnSignal();
                root.turnOnLongLights();
            }
        }

    }

}
