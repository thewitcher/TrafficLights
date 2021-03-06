import QtQuick 1.0

Rectangle {
    id: rootR
    width: 1.05; height: 5
    color: "black"
    Rectangle {
        width: 3.15; height: 1.05
        anchors.top: rootR.top
        anchors.topMargin: 1

        anchors.right: rootR.right
        anchors.rightMargin: -0.65

        transformOrigin:Item.Top
        rotation: 135
        color: "black"
    }
    Rectangle {
        width: 3.15; height: 1.05
        anchors.top: rootR.top
        anchors.topMargin: 0.4

        anchors.left: rootR.left
        anchors.leftMargin: 0.3
        transformOrigin:Item.Top
        rotation: 45
        color: "black"
    }

    Rectangle {
         width: 6; height: 1.05
         color: "black"
         anchors.left: parent.left
         anchors.leftMargin: -5
         anchors.verticalCenter: parent.verticalCenter
         anchors.verticalCenterOffset: 2
        Rectangle {
            width: 3.15; height: 1.05
            transformOrigin:Item.Left
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0.2
            rotation: -45
            color: "black"
        }
        Rectangle {
            width: 3.15; height: 1.05
            transformOrigin:Item.Left
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -0.2
            rotation: 45
            color: "black"
        }
    }
}
