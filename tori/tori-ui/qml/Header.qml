import QtQuick 2.0
import Ubuntu.Components 0.1

Rectangle {
    id: header
    height: units.gu(5)
    gradient: Gradient {
         GradientStop { position: 0.0; color: "#e7e7e7" }
         GradientStop { position: 1.0; color: "#b0b0b0" }
     }
    border.width: 1
    border.color: "gray"

    Label {
        text: "Timeline"
        fontSize: "large"
        anchors.centerIn: parent
        color: "black"
    }

    Button {
        width: units.gu(4)
        height: units.gu(4)
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: units.gu(0.5)
        anchors.rightMargin: units.gu(1)
        visible: false
    }
}
