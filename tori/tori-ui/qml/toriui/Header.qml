// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: header
    x: 0
    y: 0
    width: main.width
    height: 40
    color: "#111111"

    Item{
        Text {
            id: app_name
            text: qsTr("Tori")
            font.pointSize: 28
            color: "#81abcf"
            font.family: "Battlestar"
            x: header.x + 30
            y: header.y + 3
        }

        Rectangle{
            id: rectangle1
            color: "#3a3d42"
            radius: 20
            x: 150
            y: header.y + 5
            width: 200
            height: 30
            smooth: true

            TextInput{
                id: txt_search
                x: 10
                y: 1
                height: 28
                text: "Searchsssssssssss"
                anchors.right: parent.right
                anchors.rightMargin: 30
                cursorVisible: true
                horizontalAlignment: TextInput.AlignLeft
                anchors.left: parent.left
                anchors.leftMargin: 10
                font.pointSize: 18
                color: "#868c93"

                Image{
                    anchors.left: txt_search.right
                    source: "images/search_icon.png"
                }
            }
        }
    }
}
