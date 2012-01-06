import QtQuick 1.0

Rectangle{
    id: longLight
    width: 19.5; height: 21.5
    radius: 19.5
    color: "#c4c43b"
    opacity: 0
    scale: 0.15
    rotation: -90

    states: [
        State {
            name: "night"
            PropertyChanges { target: longLight; opacity: 1 }
            PropertyChanges { target: r; opacity: 1 }
            PropertyChanges { target: l; opacity: 1 }
            PropertyChanges { target: l1; opacity: 1 }
            PropertyChanges { target: l2; opacity: 1 }
            PropertyChanges { target: l3; opacity: 1 }
            PropertyChanges { target: l4; opacity: 1 }
        }, State {
            name: "day"
            PropertyChanges { target: longLight; opacity: 0 }
            PropertyChanges { target: r; opacity: 0 }
            PropertyChanges { target: l; opacity: 0 }
            PropertyChanges { target: l1; opacity: 0 }
            PropertyChanges { target: l2; opacity: 0 }
            PropertyChanges { target: l3; opacity: 0 }
            PropertyChanges { target: l4; opacity: 0 }
        }]

    transitions: [
        Transition { from: "*" ;to: "*"
            PropertyAnimation{
                targets: [longLight,l,r,l1,l2,l3,l4]
                properties: "opacity"; duration: 1000
            }
        }
    ]

    state: "day"

    Rectangle{
        id: r
        y:3.5; x:-30
        width: 40; height: 4
        rotation: -11
        color: "#c4c43b"
    }
    Rectangle{
        id: l
        y:13; x:-30
        width: 40; height: 4
        rotation: 15
        color: "#c4c43b"
    }
    Rectangle{
        id:l1
        y:10.5; x:-27
        width: 40; height: 4
        rotation: 9.5
        color: "#c4c43b"
    }
    Rectangle{
        id:l2
        y:6; x:-27
        width: 40; height: 4
        rotation: -6.5
        color: "#c4c43b"
    }
    Rectangle{
        id:l3
        y:7; x:-24
        width: 40; height: 4
        rotation: -4
        color: "#c4c43b"
    }
    Rectangle{
        id:l4
        y:8; x:-24
        width: 40; height: 4
        color: "#c4c43b"
    }
}
