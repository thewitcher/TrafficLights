import QtQuick 1.0
import Vehicles 1.0

Vehicles {
    width: 18
    height: 18

    onBlinkersChanged: {
        console.log("sdfsfgs")
    }

    Rectangle {
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
