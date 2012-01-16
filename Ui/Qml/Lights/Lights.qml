import QtQuick 1.0
import LightsPacket 1.0

Light {
    id: lightSignal
    width: 15; height: 42

    function setOnlyRightDirection()
    {
        right1.opacity = 1
        right2.opacity = 1
        right3.opacity = 1
    }

    function setOnlyLeftDirection()
    {
        left1.opacity = 1
        left2.opacity = 1
        left3.opacity = 1
    }

    function setOnlyStraightDirection()
    {
        straight1.opacity = 1
        straight2.opacity = 1
        straight3.opacity = 1
    }

    function setLeftAndStraightDirection()
    {
        arrowStraightAndLeft1.opacity = 1
        arrowStraightAndLeft2.opacity = 1
        arrowStraightAndLeft3.opacity = 1
    }

    function setRightAndStraightDirection()
    {
        arrowStraightAndRight1.opacity = 1
        arrowStraightAndRight2.opacity = 2
        arrowStraightAndRight3.opacity = 3
    }

    function hold()
    {
        readyToStop.running = true;
        readyToStart.running = false;
    }

    function letGo()
    {
        readyToStart.running = true;
        readyToStop.running = false;
    }

    SequentialAnimation{
        id:readyToStart
        running: false
        ParallelAnimation{
            PropertyAnimation{ target:red; property: "color"; to: "red"; duration: 500 }
            PropertyAnimation{ target:yellow; property: "color"; to: "yellow"; duration: 500 }
        }
        ParallelAnimation{
            PropertyAnimation{ target:green; property: "color"; to: "#5ff155"; duration: 500 }
            PropertyAnimation{ target:red; property: "color"; to: "darkred"; duration: 500 }
            PropertyAnimation{ target:yellow; property: "color"; to: "#808000"; duration: 500 }
        }
    }

    SequentialAnimation{
        id:readyToStop
        running: false
        ParallelAnimation{
            PropertyAnimation{ target:green; property: "color"; to: "darkgreen"; duration: 500 }
            PropertyAnimation{ target:yellow; property: "color"; to: "yellow"; duration: 500 }
        }
        ParallelAnimation{
            PropertyAnimation{ target:red; property: "color"; to: "red"; duration: 500 }
            PropertyAnimation{ target:yellow; property: "color"; to: "#808000"; duration: 500 }
        }
    }

    Rectangle {
        id:box
        width: 15
        height: 42
        color: "grey"
        border.width: 1
        border.color: "lightgrey"

        Rectangle{
            id:red
            width: 12; height: 12
            anchors.top: parent.top
            anchors.topMargin: 2
            anchors.horizontalCenter: box.horizontalCenter
            radius: 6
            color: "darkred"
            ArrowInLeft{
                id: left1
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 0.1
                opacity: 0
            }
            ArrowStraight{
                id:straight1
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 0.5
                opacity: 0
            }
            ArrowInRight{
                id:right1
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 0.1
                opacity: 0
            }
            ArrowStraightAndLeft{
                id: arrowStraightAndLeft1
                opacity: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 2.5
                anchors.verticalCenter: parent.verticalCenter
            }
            ArrowStraightAndRight{
                id: arrowStraightAndRight1
                opacity: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -2
                anchors.verticalCenter: parent.verticalCenter
            }

        }
        Rectangle{
            id:yellow
            width: 12; height: 12
            radius: 6
            color: "#808000"
            anchors.top: red.bottom
            anchors.topMargin: 2
            anchors.horizontalCenter: box.horizontalCenter
            ArrowInLeft{
                id: left2
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 0.1
                opacity: 0
            }
            ArrowStraight{
                id:straight2
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 0.5
                opacity: 0
            }
            ArrowInRight{
                id:right2
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 0.1
                opacity: 0
            }
            ArrowStraightAndLeft{
                id: arrowStraightAndLeft2
                opacity: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 2.5
                anchors.verticalCenter: parent.verticalCenter
            }
            ArrowStraightAndRight{
                id: arrowStraightAndRight2
                opacity: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -2
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Rectangle{
            id:green
            width: 12; height: 12
            anchors.top: yellow.bottom
            anchors.topMargin: 2
            anchors.horizontalCenter: box.horizontalCenter
            radius: 6
            color: "darkgreen"
            ArrowInLeft{
                id: left3
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 0.1
                opacity: 0
            }
            ArrowStraight{
                id:straight3
                anchors.centerIn: parent
                anchors.horizontalCenterOffset: 0.5
                opacity: 0
            }
            ArrowInRight{
                id:right3
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 0.1
                opacity: 0
            }
            ArrowStraightAndLeft{
                id: arrowStraightAndLeft3
                opacity: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: 2.5
                anchors.verticalCenter: parent.verticalCenter
            }
            ArrowStraightAndRight{
                id: arrowStraightAndRight3
                opacity: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -2
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
