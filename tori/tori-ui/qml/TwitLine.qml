import QtQuick 2.0

Timeline {
    Component {
        id: twitDelegate
        Twit{}
    }

    ListView {
        id: view
        anchors.fill: parent

        model: ListModel { id: twitLineModel }
        delegate: twitDelegate
        focus: true

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

    // Attach scrollbars to the right and bottom edges of the view.
    ScrollBar {
        id: verticalScrollBar
        width: 12; height: view.height-12
        anchors.right: view.right
        opacity: 0
        position: view.visibleArea.yPosition
        pageSize: view.visibleArea.heightRatio
    }

    function add_twit(username){
        twitLineModel.insert(0, {username: username});
    }

    Component.onCompleted: {
        add_twit("Gatox");
        add_twit("Diego Sarmentero");
        add_twit("Gatox");
        add_twit("Diego Sarmentero");
        add_twit("Gatox");
        add_twit("Diego Sarmentero");
        add_twit("Gatox");
        add_twit("Diego Sarmentero");
        add_twit("Gatox");
        add_twit("Diego Sarmentero");
        add_twit("Gatox");
        add_twit("Diego Sarmentero");
        add_twit("Gatox");
        add_twit("Diego Sarmentero");
    }

}
