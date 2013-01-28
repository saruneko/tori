/**
 *
 * Copyright (c) 2012 Diego Sarmentero <diego.sarmentero@ninja-ide.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

import QtQuick 2.0
import Ubuntu.Components 0.1

BaseMainContainer {
    id: writeTwit

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
        }

        TextArea {
            id: twitWrite
            width: parent.width
            contentWidth: parent.width - units.gu(1)
            height: units.gu(26)
            wrapMode: TextEdit.Wrap
            font.pixelSize: 24


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

            onClicked: main.send_twit("diegosarmentero", twitWrite.text);
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
            iconSource: "../img/icons/add_picture.png"
        }
        Button {
            height: row_send.height
            width: __size_children
            text: "Add Contact"
            color: "lightblue"
            iconSource: "../img/icons/add_contact.png"
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

    function add_account(user_name, avatar){
        var component = Qt.createComponent("SelectUser.qml");
        if (component.status == Component.Ready)
            component.createObject(usersRow, {"user_name": user_name, "avatar": avatar});
        if(usersRow.children.count == 1)
            usersRow.children[1].selected = true;
    }
}
