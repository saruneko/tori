import QtQuick 2.0
import Ubuntu.Components 0.1

Item {
    id: scrollBar

    property real position
    property real pageSize
    property int offset: units.gu(2)

    // A light, semi-transparent background
    Rectangle {
        id: background
        anchors.fill: parent
        anchors.topMargin: offset
//        anchors.bottomMargin: offset
        radius: (width / 2) - units.dp(1)
        color: "gray"
        border.width: units.dp(1)
        border.color: "black"
        opacity: 0.3
        smooth: true
    }

    // Size the bar to the required size
    Rectangle {
        x: units.dp(1)
        y: (scrollBar.position * (scrollBar.height - units.dp(2)) + units.dp(1)) + offset
        width: parent.width - units.dp(2)
        height: (scrollBar.pageSize * (scrollBar.height - units.dp(2))) - offset
        radius: (width / 2) - units.dp(1)
        color: "black"
        opacity: 0.7
        smooth: true
    }
}
