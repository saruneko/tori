import QtQuick 1.1

Rectangle {
    id: main
    anchors.centerIn: parent
    width: 800
    height: 700
    color: "#55555a"

    property int columns: 2

    Rectangle {
        id: container
        anchors.fill: parent
        anchors.margins: 8
        anchors.topMargin: 41
        color: parent.color

        Row {
            id: row
            anchors.fill: parent
            spacing: 12
            Timeline {}
            Timeline {}
        }
    }

    Header {}

    function add_column(title, user){
        var component = Qt.createComponent("Timeline.qml");
        if (component.status == Component.Ready) {
            var timeline = component.createObject(row);
            timeline.header_text = title;
            timeline.header_user = user;
        }
    }
}
