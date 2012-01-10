import QtQuick 1.0

Rectangle {
//    width:40; height:7
    //    x:55; y: 55
    width: 8; height: 1.05
    color: "black"
    Rectangle {
//        width: 25; height: 7
//        x:0; y:2
        width: 4.25; height: 1.05
        transformOrigin:Item.Right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 0.2
        rotation: 45
        color: "black"
    }
    Rectangle {
//        width: 25; height: 7
        //        x:0; y:-2
        width: 4.25; height: 1.05
        transformOrigin:Item.Right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -0.2
        rotation: -45
        color: "black"
    }
}
