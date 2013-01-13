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

            onClicked: {
                PopupUtils.open(dialog, currentAccount)
                main.showing_dialog = true;
            }
        }
        ButtonImage {
            id: btnTimeline
            width: parent.width
            height: units.gu(5)
            text: "timeline"
            color: "#34a3ec"

            onClicked: {
                toggle_buttons(btnTimeline);
                main.show_column(main.timeline, "Timeline");
            }
        }
        ButtonImage {
            id: btnMentions
            width: parent.width
            height: units.gu(5)
            text: "mentions"
            color: "transparent"

            onClicked: {
                toggle_buttons(btnMentions);
                main.show_column(main.mentions, "Mentions");
            }
        }
        ButtonImage {
            id: btnDirect
            width: parent.width
            height: units.gu(5)
            text: "direct messages"
            color: "transparent"

            onClicked: {
                toggle_buttons(btnDirect);
                main.show_column(main.directMessages, "Direct Messages");
            }
        }
        ButtonImage {
            id: btnUser
            width: parent.width
            height: units.gu(5)
            text: "gatox"
            color: "transparent"

            onClicked: {
                toggle_buttons(btnUser);
                main.show_column(main.myAccount, "Account");
            }
        }
        ButtonImage {
            id: btnSearch
            width: parent.width
            height: units.gu(5)
            text: "search"
            color: "transparent"

            onClicked: {
                toggle_buttons(btnSearch);
                main.show_column(main.search, "Search");
            }
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
