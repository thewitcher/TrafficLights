import QtQuick 1.0
import Vehicles 1.0

Vehicles {
    width: 18
    height: 18
    property alias carColor: rect.color

     Timer {
         interval: 2000; running: true; repeat: true
         onTriggered: carColor = "black"
     }

    Rectangle {
        id: rect
        anchors.centerIn: parent
        color: ( blinkers ? "green" : "black")

        width: 18
        height: 18

        Rectangle {
            anchors.top: parent.top
            color: "red"

            width: 10
            height: 10
        }
    }
}
