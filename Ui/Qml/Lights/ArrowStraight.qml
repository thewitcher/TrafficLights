import QtQuick 1.0

Rectangle {
    id: rootR
    width: 1.05; height: 7
    color: "black"
    Rectangle {
        width: 4.25; height: 1.05
        anchors.top: rootR.top
        anchors.topMargin: 1

        anchors.right: rootR.right
        anchors.rightMargin: -0.65

        transformOrigin:Item.Top
        rotation: 135
        color: "black"
    }
    Rectangle {
        width: 4.25; height: 1.05
        anchors.top: rootR.top
        anchors.topMargin: 0.4

        anchors.left: rootR.left
        anchors.leftMargin: 0.05
        transformOrigin:Item.Top
        rotation: 45
        color: "black"
    }
}
