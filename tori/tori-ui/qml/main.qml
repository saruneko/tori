import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.Popups 0.1


Rectangle {
    width: units.gu(65)
    height: units.gu(100)

    Component {
         id: dialog
         Dialog {
             id: dialogue
             title: "Select Account"
             AccountsList {}
             Button {
                 text: "Close"
                 onClicked: PopupUtils.close(dialogue)
             }
         }
    }

    MenuBar {
        id: menuBar
        anchors.left: parent.left
    }

    Header {
        id: header
        anchors.left: menuBar.right
        width: parent.width - menuBar.width
    }

    TwitLine {
        id: twitLine
        anchors.left: menuBar.right
        anchors.top: header.bottom
        width: parent.width - menuBar.width
        height:parent.height - header.height
    }
}
