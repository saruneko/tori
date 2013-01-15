import QtQuick 2.0

Rectangle {
    id: timeline
    color: main.timeline_background_color

    Behavior on scale {
        SequentialAnimation {
            PropertyAnimation { duration: 400 }
            PropertyAction { target: timeline; property: "scale"; value: 1 }
            PropertyAction { target: timeline; property: "x"; value: main.width }
        }
    }

    Behavior on x {
        SequentialAnimation{
            PropertyAction { target: timeline; property: "x"; value: main.width }
            PropertyAnimation { duration: 400 }
        }
    }

}
