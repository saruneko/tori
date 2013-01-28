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
    id: twit
    width: parent.width
    height: units.gu(16)
    border.width: units.dp(1)
    border.color: "#efefef"
    color: "transparent"

    property string twitId: twit_id

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            main.show_twit(twitId);
        }

        onEntered: show_buttons();
        onExited: hide_buttons();
    }

    UbuntuShape{
        id: picture_id
        width: units.gu(9)
        height: units.gu(9)
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

    Rectangle {
        id: messageArea
        anchors.left: picture_id.right
        anchors.top: parent.top
        anchors.leftMargin: units.gu(1)
        anchors.topMargin: units.gu(1.5)
        width: parent.width - picture_id.width
        Column {
            id: twit_content
            spacing: units.gu(1)
            anchors.fill: parent
            Label{
                id: username_id
                text: username
                color: "#222222"
                fontSize: "large"
                font.bold: true
            }
            Label {
                id: message_id
                text: "Esto es un twit para la aplicacion Tori, y deberia tener 140 caracteres, asi que: blah blah blah2 blah2 blah3 blah3 y no termina mas esto..."
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                width: twit.width - picture_id.width - units.gu(3)
                fontSize: "medium"
                color: "#323232"
            }
            Label {
                id: origin_id
                text: twit_origin
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                width: twit.width - picture_id.width - units.gu(3)
                fontSize: "small"
                color: "gray"
            }
        }

        Row{
            anchors.right: parent.right
            anchors.rightMargin: units.gu(3)
            anchors.top: parent.top
            spacing: units.gu(1)

            Label{
                id: time
                text: "1 day"
                fontSize: "small"
                color: "gray"
            }

            ButtonImage{
                id: reply
                width: units.gu(3)
                height: units.gu(3)
                image.source: "../img/icons/reply_small.png"
                visible: false

                onHoveredChanged: {
                    if(hovered){
                        show_buttons();
                    }else{
                        hide_buttons();
                    }
                }
            }
            ButtonImage{
                id: retweet
                width: units.gu(3)
                height: units.gu(3)
                image.source: "../img/icons/retweet_small.png"
                visible: false

                onHoveredChanged: {
                    if(hovered){
                        show_buttons();
                    }else{
                        hide_buttons();
                    }
                }
            }
            ButtonImage{
                id: favorite
                width: units.gu(3)
                height: units.gu(3)
                image.source: "../img/icons/favorites_small.png"
                visible: false

                onHoveredChanged: {
                    if(hovered){
                        show_buttons();
                    }else{
                        hide_buttons();
                    }
                }
            }
        }
    }

    function show_buttons(){
        if(!main.showing_dialog){
            time.visible = false;
            retweet.visible = true;
            reply.visible = true;
            favorite.visible = true;
            color = "#f0f7f7";
        }
    }

    function hide_buttons(){
        time.visible = true;
        color = "transparent";
        retweet.visible = false;
        reply.visible = false;
        favorite.visible = false;
    }

}
