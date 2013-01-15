import QtQuick 2.0
import Ubuntu.Components 0.1

BaseMainContainer {
    id: writeTwit

    property list<SelectUser> users: [SelectUser{selected: true}, SelectUser{}]

    property int __size_children: (row_add.width / row_add.children.length) - row_add.spacing - units.gu(1)

    Column {
        id: writeArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: units.gu(1)
        spacing: units.gu(2)
        height: usersRow.height + twitWrite.height + (spacing * (children.length - 1))

        Row {
            id: usersRow
            height: units.gu(6)
            spacing: units.gu(1)
            children: users
        }

        TextArea {
            id: twitWrite
            width: parent.width
            contentWidth: parent.width - units.gu(1)
            height: units.gu(36)
            wrapMode: TextEdit.Wrap
            fontSize: "x-large"


            onLengthChanged: {
                update_counter(length);
            }
        }
    }

    Row {
        id: row_send
        anchors.right: parent.right
        anchors.rightMargin: units.gu(2)
        anchors.top: writeArea.bottom
        anchors.topMargin: units.gu(2)
        height: units.gu(6)
        spacing: units.gu(2)
        Label {
            id: counter
            text: "140"
            height: row_send.height
            fontSize: "large"
            color: "black"
            verticalAlignment: Text.AlignVCenter
        }
        Button {
            height: row_send.height
            width: units.gu(16)
            text: "Send"
            color: "orange"
        }
    }

    Row {
        id: row_add
        anchors.left: parent.left
        anchors.leftMargin: units.gu(2)
        anchors.top: row_send.bottom
        anchors.topMargin: units.gu(4)
        height: units.gu(6)
        width: parent.width
        spacing: units.gu(2)

        Button {
            height: row_send.height
            width: __size_children
            text: "Add Picture"
            color: "lightblue"
        }
        Button {
            height: row_send.height
            width: __size_children
            text: "Add Contact"
            color: "lightblue"
        }

        function get_child_size(){
            return
        }
    }

    function update_counter(len){
        var toWrite = 140 - len;
        if(toWrite >= 0){
            counter.color = "black";
        }else{
            counter.color = "red";
        }

        counter.text = toWrite;
    }

    Component.onCompleted: {
//        users = [];
    }
}
