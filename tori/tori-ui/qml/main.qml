import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.Popups 0.1


Rectangle {
    id: main
    width: units.gu(65)
    height: units.gu(100)

    property variant timeline_background_color: "#f9f9f9"
    property alias timeline: main_timeline
    property alias mentions: mentions_timeline
    property alias directMessages: directMessages_timeline
    property alias myAccount: myAccount_timeline
    property alias search: search_timeline
    property alias write: write_twit
    property variant current_line: main_timeline
    property bool showing_dialog: false

    color: timeline_background_color

    Component {
         id: dialog
         Dialog {
             id: dialogue
             z: current_line.z + 1
             title: "Select Account"
             AccountsList {}
             Button {
                 text: "Close"
                 onClicked: {
                     showing_dialog = false;
                     PopupUtils.close(dialogue)
                 }
             }
         }
    }

    MenuBar {
        id: menuBar
        anchors.left: parent.left
    }

    TwitLine {
        id: main_timeline
        x: menuBar.width
        anchors.top: header.bottom
        width: parent.width - menuBar.width
        height:parent.height - header.height
    }
    TwitLine {
        id: mentions_timeline
        x: main.width
        anchors.top: header.bottom
        width: parent.width - menuBar.width
        height:parent.height - header.height
    }
    TwitLine {
        id: directMessages_timeline
        x: main.width
        anchors.top: header.bottom
        width: parent.width - menuBar.width
        height:parent.height - header.height
    }
    AccountTimeline {
        id: myAccount_timeline
        x: main.width
        anchors.top: header.bottom
        width: parent.width - menuBar.width
        height:parent.height - header.height
    }
    SearchTimeline {
        id: search_timeline
        x: main.width
        anchors.top: header.bottom
        width: parent.width - menuBar.width
        height:parent.height - header.height
    }

    WriteTwit {
        id: write_twit
        x: main.width
        anchors.top: header.bottom
        width: parent.width - menuBar.width
        height:parent.height - header.height
    }

    ReadTwit {
        id: read_twit
        x: main.width
        anchors.top: header.bottom
        width: parent.width - menuBar.width
        height:parent.height - header.height
    }

    Header {
        id: header
        z: current_line.z + 1;
        anchors.left: menuBar.right
        width: parent.width - menuBar.width
    }

    function show_column(line, header_text){
        if(line != current_line){
            current_line.scale = 0.5
            line.z = current_line.z + 1;
            header.title = header_text;
            line.x = menuBar.width;
            current_line = line;
        }
    }
}
