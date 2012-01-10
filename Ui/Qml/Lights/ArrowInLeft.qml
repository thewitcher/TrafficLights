import QtQuick 1.0

Rectangle {
     width: 8; height: 1.05
    color: "black"
    Rectangle {
        width: 4.25; height: 1.05
        transformOrigin:Item.Left
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 0.2
        rotation: -45
        color: "black"
    }
    Rectangle {
        width: 4.25; height: 1.05
        transformOrigin:Item.Left
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -0.2
        rotation: 45
        color: "black"
    }
}
