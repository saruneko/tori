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
    Column {
        anchors.fill: parent
        Rectangle {
            id: details
            z: 2
            width: parent.width
            height: units.gu(34)
            Image{
                anchors.fill: parent
                fillMode: Image.Tile
                source: "../img/dark_background.png"
            }

            UbuntuShape{
                id: picture_id
                width: units.gu(16)
                height: units.gu(16)
                color: "transparent"
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: units.gu(1)
                anchors.topMargin: units.gu(1)
                image: Image {
                    source: "../img/gatox_face.png"
                    anchors.fill: parent
                    anchors.centerIn: parent
                    asynchronous: true
                }
            }

            Column {
                anchors.left: picture_id.right
                anchors.leftMargin: units.gu(1)
                anchors.top: parent.top
                anchors.topMargin: units.gu(5)
                spacing: units.dp(2)
                Label{
                    id: displayname
                    text: "Gatox"
                    color: "white"
                    fontSize: "x-large"
                    font.bold: true
                    width: details.width - picture_id.width - units.gu(5)
                    horizontalAlignment: Text.AlignHCenter
                }
                Label{
                    id: username
                    text: "@diegosarmentero"
                    color: "white"
                    fontSize: "large"
                    width: details.width - picture_id.width - units.gu(5)
                    horizontalAlignment: Text.AlignHCenter
                }
                Label{
                    id: follow_info
                    text: "Following each other"
                    color: "gray"
                    fontSize: "small"
                    width: details.width - picture_id.width - units.gu(5)
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            Label{
                width: details.width
                anchors.top: picture_id.bottom
                anchors.left: details.left
                anchors.right: details.right
                anchors.topMargin: units.gu(1)
                anchors.leftMargin: units.gu(4)
                anchors.rightMargin: units.gu(4)
                text: "Creator and Developer of NINJA-IDE! - Software Engineer @Canonical - Programmer... Computer Geek... Human Being?? - In Flatland! · http://diegosarmentero.com "
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                fontSize: "medium"
                color: "white"
                horizontalAlignment: Text.AlignHCenter
            }

            Row {
                width: details.width
                anchors.left: details.left
                anchors.right: details.right
                anchors.bottom: details.bottom
                anchors.leftMargin: units.gu(2)
                anchors.rightMargin: units.gu(2)
                anchors.bottomMargin: units.gu(1)
                spacing: units.gu(2)
                Button {
                    width: (details.width / 2) - units.gu(3)
                    text: "Followers"
                    height: units.gu(5)
                    iconSource: "../img/icons/followers.png"
                }
                Button {
                    width: (details.width / 2) - units.gu(3)
                    height: units.gu(5)
                    text: "Following"
                    iconSource: "../img/icons/following.png"
                }
            }
        }
        TwitLine {
            width: parent.width
            height: parent.height - details.height
        }
    }
}
