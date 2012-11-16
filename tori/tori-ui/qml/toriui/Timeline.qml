import QtQuick 1.1

ShadowRectangle {
    id: timeline
    width: parent.width / main.columns - container.anchors.margins
    height: parent.height- 150
    color: "#26282a"
    radius: 5

    property alias header_text: txt_title.text
    property alias header_user: txt_username.text

    Flickable{
        id: view
        anchors.fill: parent
        anchors.topMargin: 40
        contentWidth: timeline_column.width
        contentHeight: timeline_column.height

        Column{
            id: timeline_column
            spacing: 5

            move: Transition {
                 NumberAnimation { properties: "y"; easing.type: Easing.OutBounce }
             }
             add: Transition {
                 NumberAnimation { properties: "y"; easing.type: Easing.OutQuad }
             }

            Rectangle {
                height: 1
                width: timeline.width
                color: "transparent"
            }

            Twit{}
            Twit{color: "#323436"}
            Twit{}
            Twit{color: "#323436"}
            Twit{}
            Twit{color: "#323436"}
            Twit{}
            Twit{}
            Twit{color: "#323436"}
            Twit{}
            Twit{color: "#323436"}
            Twit{}
            Twit{color: "#323436"}
            Twit{}
        }

        // Only show the scrollbars when the view is moving.
        states: State {
            name: "ShowBars"
            when: view.movingVertically
            PropertyChanges { target: verticalScrollBar; opacity: 1 }
        }

        transitions: Transition {
            NumberAnimation { properties: "opacity"; duration: 400 }
        }
    }

    Rectangle {
        id: timeline_title
        height: 40
        width: timeline.width
        border.color: "#525458"
        border.width: 2
        color: "#3a3d42"
        radius: 5
        Item {
            anchors.fill: parent
            anchors.topMargin: 8
            anchors.leftMargin: 20
            Row{
                anchors.fill: parent
                spacing: 8
                Text {
                    id: txt_title
                    text: qsTr("1. Timeline")
                    color: "white"
                    font.pointSize: 16
                    font.bold: true
                }
                Text {
                    id: txt_username
                    text: qsTr("@diegosarmentero")
                    color: "white"
                    font.pointSize: 14
                }
            }
        }
    }

    // Attach scrollbars to the right and bottom edges of the view.
    ScrollBar {
        id: verticalScrollBar
        width: 12; height: view.height-12
        anchors.right: view.right
        opacity: 0
        orientation: Qt.Vertical
        position: view.visibleArea.yPosition
        pageSize: view.visibleArea.heightRatio
    }

    function add_twit(){
        var component = Qt.createComponent("Twit.qml");
        if (component.status == Component.Ready) {
            var newTwit = component.createObject(timeline_column);
            newTwit.message = "Nuevo Twit!";
            newTwit.username = "Gatox";
            newTwit.nickname = "@gatox";
        }
    }

    Component.onCompleted: {
        timeline.add_twit();
    }
}
