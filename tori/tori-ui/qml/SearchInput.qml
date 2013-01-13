import QtQuick 2.0
import Ubuntu.Components 0.1

Rectangle {
    id: search_box
    color: "#3a3d42"
    radius: units.gu(3)
    smooth: true

    Behavior on border.color { ColorAnimation{duration: 200} }

    TextInput{
        id: txt_search
        x: 10
        y: 4
        width: 158
        height: 28
        text: "Search"
        anchors.right: parent.right
        anchors.rightMargin: 32
        cursorVisible: true
        horizontalAlignment: TextInput.AlignLeft
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pointSize: 14
        color: "#868c93"
        smooth: true

        Image{
            x: 160
            y: -2
            anchors.leftMargin: 0
            anchors.left: txt_search.right
            source: "../img/search_icon.png"

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    txt_search.selectAll();
                    txt_search.focus = true;
                }
                onEntered: {
                    search_box.border.color = "white";
                }
                onExited: {
                    search_box.border.color = "#3a3d42";
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                txt_search.selectAll();
                txt_search.focus = true;
            }
            onEntered: {
                search_box.border.color = "white";
            }
            onExited: {
                search_box.border.color = "#3a3d42";
            }
        }
    }
}
