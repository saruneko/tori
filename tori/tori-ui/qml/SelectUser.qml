import QtQuick 2.0
import Ubuntu.Components 0.1

Rectangle {
    width: units.gu(6)
    height: units.gu(6)

    property bool selected: false

    Image {
        id: img
        source: "../img/gatox_face.png"
        width: units.gu(6)
        height: units.gu(6)
        asynchronous: true
    }

    Rectangle {
        id: selection
        anchors.fill: img
        opacity: 0.6
        color: "gray";
        border.color: "gray";
        border.width: units.dp(3)
        radius: units.dp(3)
        smooth: true

        Behavior on color { ColorAnimation { duration: 300 } }
        Behavior on border.color { ColorAnimation { duration: 300 } }
        Behavior on opacity { NumberAnimation { duration: 300 } }
    }

    onSelectedChanged: {
        if(selected){
            selection.color = "transparent";
            selection.border.color = "#ff7623";
            selection.opacity = 1;
        }else{
            selection.opacity = 0.6;
            selection.color = "gray";
            selection.border.color = "gray";
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: selected = !selected;
    }
}
