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
import Ubuntu.Components.Popups 0.1

Rectangle {
    width: units.gu(12)
    height: parent.height
    color: "#212121"

    Column {
        anchors.fill: parent
        anchors.margins: units.gu(1)
        anchors.topMargin: units.gu(2)
        anchors.bottomMargin: units.gu(10)
        spacing: units.gu(2)

        Button {
            id: currentAccount
            width: parent.width
            height: units.gu(10)
            color: "transparent"
            UbuntuShape{
                width: parent.width
                height: parent.height
                color: "transparent"
                image: Image {
                    id: img
                    source: "../img/gatox_face.png"
                    anchors.fill: parent
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                }
            }

            onClicked: {
                main.showing_dialog = true;
                PopupUtils.open(dialog, currentAccount)
            }
        }

        ButtonImage {
            id: btnTimeline
            width: parent.width
            height: units.gu(5)
            color: "#34a3ec"
            image.source: "../img/icons/timeline.png"

            onClicked: {
                toggle_buttons(btnTimeline);
                main.show_column(main.timeline, "Timeline");
            }
        }
        ButtonImage {
            id: btnMentions
            width: parent.width
            height: units.gu(5)
            color: "transparent"
            image.source: "../img/icons/mentions.png"

            onClicked: {
                toggle_buttons(btnMentions);
                main.show_column(main.mentions, "Mentions");
            }
        }
        ButtonImage {
            id: btnDirect
            width: parent.width
            height: units.gu(5)
            color: "transparent"
            image.source: "../img/icons/direct_messages.png"

            onClicked: {
                toggle_buttons(btnDirect);
                main.show_column(main.directMessages, "Direct Messages");
            }
        }
        ButtonImage {
            id: btnUser
            width: parent.width
            height: units.gu(5)
            color: "transparent"
            image.source: "../img/icons/my_account.png"

            onClicked: {
                toggle_buttons(btnUser);
                main.show_column(main.myAccount, "Account");
            }
        }
        ButtonImage {
            id: btnSearch
            width: parent.width
            height: units.gu(5)
            color: "transparent"
            image.source: "../img/icons/search.png"

            onClicked: {
                toggle_buttons(btnSearch);
                main.show_column(main.search, "Search");
            }
        }
    }

    ButtonImage {
        id: btnWrite
        width: parent.width
        height: units.gu(6)
        color: "transparent"
        anchors.bottom: parent.bottom
        image.source: "../img/icons/write_tweet.png"

        onClicked: {
            toggle_buttons(btnWrite);
            main.show_column(main.write, "Write Twit!");
        }
    }

    function toggle_buttons(button){
        btnTimeline.color = "transparent";
        btnMentions.color = "transparent";
        btnDirect.color = "transparent";
        btnUser.color = "transparent";
        btnSearch.color = "transparent";
        btnWrite.color = "transparent";
        if(button){
            button.color = "#34a3ec";
        }
    }
}
