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

Rectangle {
    id: search_box
    color: "#3a3d42"
    radius: units.gu(3)
    smooth: true

    Behavior on border.color { ColorAnimation{duration: 200} }

    TextInput{
        id: txt_search
        x: 10
        y: 4
        width: 158
        height: 28
        text: "Search"
        anchors.right: parent.right
        anchors.rightMargin: 32
        cursorVisible: true
        horizontalAlignment: TextInput.AlignLeft
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pointSize: 14
        color: "#868c93"
        smooth: true

        Image{
            x: 160
            y: -2
            anchors.leftMargin: 0
            anchors.left: txt_search.right
            source: "../img/search_icon.png"

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    txt_search.selectAll();
                    txt_search.focus = true;
                }
                onEntered: {
                    search_box.border.color = "white";
                }
                onExited: {
                    search_box.border.color = "#3a3d42";
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                txt_search.selectAll();
                txt_search.focus = true;
            }
            onEntered: {
                search_box.border.color = "white";
            }
            onExited: {
                search_box.border.color = "#3a3d42";
            }
        }
    }
}
