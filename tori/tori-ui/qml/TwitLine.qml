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

BaseMainContainer {
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
    CustomScrollBar {
        id: verticalScrollBar
        width: 12; height: view.height-12
        anchors.right: view.right
        opacity: 0
        position: view.visibleArea.yPosition
        pageSize: view.visibleArea.heightRatio
    }

    function add_twit(username, origin){
        twitLineModel.insert(0, {username: username, twit_id: "", twit_origin: origin});
    }

    Component.onCompleted: {
        add_twit("Gatox", "Retweeted by @diegosarmentero");
        add_twit("Diego Sarmentero", "diegosarmentero");
        add_twit("Gatox", "Retweeted by @diegosarmentero");
        add_twit("Diego Sarmentero", "diegosarmentero");
        add_twit("Gatox", "Retweeted by @diegosarmentero");
        add_twit("Diego Sarmentero", "diegosarmentero");
        add_twit("Gatox", "Retweeted by @diegosarmentero");
        add_twit("Diego Sarmentero", "diegosarmentero");
        add_twit("Gatox", "Retweeted by @diegosarmentero");
        add_twit("Diego Sarmentero", "diegosarmentero");
        add_twit("Gatox", "Retweeted by @diegosarmentero");
        add_twit("Diego Sarmentero", "diegosarmentero");
        add_twit("Gatox", "Retweeted by @diegosarmentero");
        add_twit("Diego Sarmentero", "diegosarmentero");
    }

}
