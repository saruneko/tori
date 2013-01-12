import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.Popups 0.1

Rectangle {
    width: units.gu(12)
    height: parent.height
    color: "#212121"

    Column {
        anchors.fill: parent
        anchors.margins: units.gu(1)
        anchors.topMargin: units.gu(2)
        anchors.bottomMargin: units.gu(10)
        spacing: units.gu(2)
        Button {
            id: currentAccount
            width: parent.width
            height: units.gu(10)
            color: "transparent"
            Image {
                id: img
                source: "../img/gatox_face.png"
                anchors.fill: parent
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
            }
            Rectangle { // rounded corners for img
                anchors.fill: img
                color: "transparent"
                border.color: "#212121" // color of background
                border.width: units.gu(1)
                radius: units.gu(1)
            }

            onClicked: PopupUtils.open(dialog, currentAccount)
        }
        ButtonImage {
            id: btnTimeline
            width: parent.width
            height: units.gu(5)
            text: "timeline"
            color: "#34a3ec"

            onClicked: toggle_buttons(btnTimeline)
        }
        ButtonImage {
            id: btnMentions
            width: parent.width
            height: units.gu(5)
            text: "mentions"
            color: "transparent"

            onClicked: toggle_buttons(btnMentions)
        }
        ButtonImage {
            id: btnDirect
            width: parent.width
            height: units.gu(5)
            text: "direct messages"
            color: "transparent"

            onClicked: toggle_buttons(btnDirect)
        }
        ButtonImage {
            id: btnUser
            width: parent.width
            height: units.gu(5)
            text: "gatox"
            color: "transparent"

            onClicked: toggle_buttons(btnUser)
        }
        ButtonImage {
            id: btnSearch
            width: parent.width
            height: units.gu(5)
            text: "search"
            color: "transparent"

            onClicked: toggle_buttons(btnSearch)
        }
    }

    Button {
        width: parent.width
        height: units.gu(8)
        color: "lightblue"
        text: "write"
        anchors.bottom: parent.bottom
    }

    function toggle_buttons(button){
        btnTimeline.color = "transparent";
        btnMentions.color = "transparent";
        btnDirect.color = "transparent";
        btnUser.color = "transparent";
        btnSearch.color = "transparent";
        button.color = "#34a3ec";
    }
}
