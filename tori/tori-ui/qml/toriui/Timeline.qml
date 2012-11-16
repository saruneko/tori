import QtQuick 1.1

ShadowRectangle {
    id: timeline
    width: parent.width / main.columns - container.anchors.margins
    height: parent.height- 150
    color: "#26282a"
    radius: 5

    property alias header_text: txt_title.text
    property alias header_user: txt_username.text

    Component {
        id: twitDelegate
        Twit{}
    }

    ListView {
        id: view
        anchors.fill: parent
        anchors.topMargin: 40

        model: TimelineModel { id: timelineModel }
        delegate: twitDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true

//            Twit{color: "#323436"}
//            Twit{}


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

    function add_twit(username){
        timelineModel.insert(0, {username: username})
    }

    Component.onCompleted: {
        timeline.add_twit("Gatox");
        timeline.add_twit("Diego Sarmentero");
        timeline.add_twit("Gatox");
        timeline.add_twit("Diego Sarmentero");
        timeline.add_twit("Gatox");
        timeline.add_twit("Diego Sarmentero");
        timeline.add_twit("Gatox");
        timeline.add_twit("Diego Sarmentero");
        timeline.add_twit("Gatox");
        timeline.add_twit("Diego Sarmentero");
        timeline.add_twit("Gatox");
        timeline.add_twit("Diego Sarmentero");
        timeline.add_twit("Gatox");
        timeline.add_twit("Diego Sarmentero");
        view.currentIndex = 6;
    }
}
