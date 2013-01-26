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

Item {
    id: scrollBar

    property real position
    property real pageSize
    property int offset: units.gu(2)

    // A light, semi-transparent background
    Rectangle {
        id: background
        anchors.fill: parent
        anchors.topMargin: offset
        radius: (width / 2) - units.dp(1)
        color: "gray"
        border.width: units.dp(1)
        border.color: "black"
        opacity: 0.3
        smooth: true
    }

    // Size the bar to the required size
    Rectangle {
        x: units.dp(1)
        y: (scrollBar.position * (scrollBar.height - units.dp(2)) + units.dp(1)) + offset
        width: parent.width - units.dp(2)
        height: (scrollBar.pageSize * (scrollBar.height - units.dp(2))) - offset
        radius: (width / 2) - units.dp(1)
        color: "black"
        opacity: 0.7
        smooth: true
    }
}
