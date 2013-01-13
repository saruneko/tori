import QtQuick 2.0

Rectangle {
    color: main.timeline_background_color

    Behavior on x {
        SequentialAnimation{
            PropertyAction { property: "x"; value: main.width }
            PropertyAnimation { duration: 400 }
        }
    }
}
