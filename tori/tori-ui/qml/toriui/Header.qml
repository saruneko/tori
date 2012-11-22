// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: header
    x: 0
    y: 0
    width: main.width
    height: 40
    color: "#111111"

    Row {
        spacing: 10
        Item{
            Text {
                id: app_name
                text: qsTr("Tori")
                font.pointSize: 28
                color: "#81abcf"
                font.family: "Battlestar"
                anchors.fill: parent
                anchors.margins: 4
                anchors.leftMargin: 30
            }
        }
    }
}
