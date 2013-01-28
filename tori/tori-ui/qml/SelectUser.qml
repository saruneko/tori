/**
 *
 * Copyright (c) 2013 Diego Sarmentero <diego.sarmentero@ninja-ide.org>
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
    width: units.gu(6)
    height: units.gu(6)

    property string user_name: ""
    property alias avatar: img.source
    property bool selected: false

    Image {
        id: img
        source: ""
        width: units.gu(6)
        height: units.gu(6)
        asynchronous: true
    }

    Rectangle {
        id: selection
        anchors.fill: img
        opacity: 0.6
        color: "gray";
        border.color: "gray";
        border.width: units.dp(3)
        radius: units.dp(3)
        smooth: true

        Behavior on color { ColorAnimation { duration: 300 } }
        Behavior on border.color { ColorAnimation { duration: 300 } }
        Behavior on opacity { NumberAnimation { duration: 300 } }
    }

    onSelectedChanged: {
        if(selected){
            selection.color = "transparent";
            selection.border.color = "#ff7623";
            selection.opacity = 1;
        }else{
            selection.opacity = 0.6;
            selection.color = "gray";
            selection.border.color = "gray";
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: selected = !selected;
    }
}
