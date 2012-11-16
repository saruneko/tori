// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: main
    width: 800
    height: 750
    color: "#55555a"

    property int columns: 2

    Rectangle {
        id: container
        anchors.fill: parent
        anchors.margins: 8
        anchors.topMargin: 48
        color: parent.color

        Row {
            id: row
            anchors.fill: parent
            spacing: 12
            Timeline {}
            Timeline {
                header_text: "2. Direct Messages"
                header_user: "@ninja-ide"
            }
        }
    }

    Header {}
}
