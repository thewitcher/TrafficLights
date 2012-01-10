import QtQuick 1.0

Rectangle {
    id: rootR
//    width:7; height:40
    width: 1.05; height: 7
//    x:35; y: 50
    color: "black"
    Rectangle {
//        width: 25; height: 7
//        x:-12.5; y:8.5
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
//        width: 25; height: 7
//        x:0.5; y:3.5
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
