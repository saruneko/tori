import QtQuick 2.0
import Ubuntu.Components 0.1

Button {
    id: buttonImage

    property alias image: img

    Image {
        id: img
        source: ""
        anchors.fill: parent
        anchors.margins: 2
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        z: 1
    }

    Behavior on color { ColorAnimation { duration: 200 } }
}
