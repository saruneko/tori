import QtQuick 2.0

Item {
    id: scrollBar

    property real position
    property real pageSize
    property variant orientation : Qt.Vertical
    property int offset: 50
    property real to_read: 0.33

    // A light, semi-transparent background
    Rectangle {
        id: background
        anchors.fill: parent
        anchors.topMargin: offset
        radius: orientation == Qt.Vertical ? (width/2 - 1) : (height/2 - 1)
        color: "white"
        opacity: 0.3
        gradient: Gradient {
             GradientStop { position: 0.0; color: "yellow" }
             GradientStop { position: to_read; color: "white" }
         }
        smooth: true
    }

    // Size the bar to the required size, depending upon the orientation.
    Rectangle {
        x: orientation == Qt.Vertical ? 1 : (scrollBar.position * (scrollBar.width-2) + 1)
        y: orientation == Qt.Vertical ? (scrollBar.position * (scrollBar.height-2) + 1) + offset : 1
        width: orientation == Qt.Vertical ? (parent.width-2) : (scrollBar.pageSize * (scrollBar.width-2))
        height: orientation == Qt.Vertical ? (scrollBar.pageSize * (scrollBar.height-2)) - offset : (parent.height-2)
        radius: orientation == Qt.Vertical ? (width/2 - 1) : (height/2 - 1)
        color: "black"
        opacity: 0.7
        smooth: true
    }
}
