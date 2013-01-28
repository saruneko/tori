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

Rectangle {
    id: timeline
    color: main.timeline_background_color

    Behavior on scale {
        SequentialAnimation {
            PropertyAnimation { duration: 400 }
            PropertyAction { target: timeline; property: "scale"; value: 1 }
            PropertyAction { target: timeline; property: "x"; value: main.width }
        }
    }

    Behavior on x {
        SequentialAnimation{
            PropertyAction { target: timeline; property: "x"; value: main.width }
            PropertyAnimation { duration: 400 }
        }
    }

}
