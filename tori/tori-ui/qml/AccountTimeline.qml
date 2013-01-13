import QtQuick 2.0
import Ubuntu.Components 0.1

Timeline {
    Column {
        anchors.fill: parent
        Rectangle {
            id: details
            z: 2
            width: parent.width
            height: units.gu(34)
            Image{
                anchors.fill: parent
                fillMode: Image.Tile
                source: "../img/account_background.png"
            }

            Image {
                id: picture_id
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: units.gu(1)
                anchors.topMargin: units.gu(1)
                source: "../img/gatox_face.png"
                width: units.gu(16)
                height: units.gu(16)
                asynchronous: true
            }
            Column {
                anchors.left: picture_id.right
                anchors.leftMargin: units.gu(1)
                anchors.top: parent.top
                anchors.topMargin: units.gu(5)
                spacing: units.dp(2)
                Label{
                    id: displayname
                    text: "Gatox"
                    color: "white"
                    fontSize: "x-large"
                    font.bold: true
                    width: details.width - picture_id.width - units.gu(5)
                    horizontalAlignment: Text.AlignHCenter
                }
                Label{
                    id: username
                    text: "@diegosarmentero"
                    color: "white"
                    fontSize: "large"
                    width: details.width - picture_id.width - units.gu(5)
                    horizontalAlignment: Text.AlignHCenter
                }
                Label{
                    id: follow_info
                    text: "Following each other"
                    color: "gray"
                    fontSize: "small"
                    width: details.width - picture_id.width - units.gu(5)
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Label{
                width: details.width
                anchors.top: picture_id.bottom
                anchors.left: details.left
                anchors.right: details.right
                anchors.topMargin: units.gu(1)
                anchors.leftMargin: units.gu(4)
                anchors.rightMargin: units.gu(4)
                text: "Creator and Developer of NINJA-IDE! - Software Engineer @Canonical - Programmer... Computer Geek... Human Being?? - In Flatland! · http://diegosarmentero.com "
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                fontSize: "medium"
                color: "white"
                horizontalAlignment: Text.AlignHCenter
            }

            Row {
                width: details.width
                anchors.left: details.left
                anchors.right: details.right
                anchors.bottom: details.bottom
                anchors.leftMargin: units.gu(2)
                anchors.rightMargin: units.gu(2)
                anchors.bottomMargin: units.gu(1)
                spacing: units.gu(2)
                Button {
                    width: (details.width / 2) - units.gu(3)
                    text: "Followers"
                }
                Button {
                    width: (details.width / 2) - units.gu(3)
                    text: "Following"
                }
            }
        }
        TwitLine {
            width: parent.width
            height: parent.height - details.height
        }
    }
}
