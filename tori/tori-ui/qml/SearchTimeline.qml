import QtQuick 2.0
import Ubuntu.Components 0.1

BaseMainContainer {
    id: searchTimeline
    Column {
        anchors.fill: parent
        Rectangle {
            id: input
            z: 2
            width: parent.width
            height: units.gu(6)
            Image{
                anchors.fill: parent
                fillMode: Image.Tile
                source: "../img/dark_background.png"
            }

            SearchInput {
                width: parent.width - units.gu(2)
                height: units.gu(4)
                anchors.top: input.top
                anchors.topMargin: units.gu(1)
                anchors.left: input.left
                anchors.leftMargin: units.gu(1)
            }
        }

        TwitLine {
            width: parent.width
            height: parent.height - input.height
        }
    }
}
