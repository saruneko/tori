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
    id: writeTwit

    Column {
        anchors.fill: parent
        anchors.margins: units.gu(1)
        spacing: units.gu(2)
        UbuntuShape {
            id: details
            z: 2
            width: parent.width
            height: units.gu(33)
            color: main.timeline_background_color

            Column {
                anchors.fill: parent
                anchors.margins: units.gu(1)
                spacing: units.gu(2)
                Label {
                    id: twit_text
                    color: "#323232"
                    text: "Esto es un twit para la aplicacion <a href='http://saruneko.org/tori'>Tori</a>, y deberia tener 140 caracteres, asi que: blah blah blah2 blah2 blah3 blah3 y no termina mas esto..."
                    fontSize: "large"
                    width: parent.width
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    smooth: true
                }

                Row {
                    spacing: units.gu(2)
                    UbuntuShape{
                        id: picture_id
                        width: units.gu(9)
                        height: units.gu(9)
                        color: "transparent"
                        image: Image {
                            source: "../img/gatox_face.png"
                            anchors.fill: parent
                            anchors.centerIn: parent
                            asynchronous: true
                        }
                    }

                    Column {
                        spacing: units.gu(1)

                        Label {
                            text: "Diego Sarmentero"
                            color: "#323232"
                        }
                        Label {
                            text: "30 minutes ago"
                            color: "#323232"
                        }
                        Label {
                            text: "Tue 15 January 1:00pm via Twitter"
                            fontSize: "small"
                        }
                    }
                }

                Row {
                    spacing: units.gu(2)
                    ButtonImage{
                        id: reply
                        width: units.gu(6)
                        height: units.gu(6)
                        image.source: "../img/icons/reply.png"
                    }
                    ButtonImage{
                        id: retweet
                        width: units.gu(6)
                        height: units.gu(6)
                        image.source: "../img/icons/retweet.png"
                    }
                    ButtonImage{
                        id: favorite
                        width: units.gu(6)
                        height: units.gu(6)
                        image.source: "../img/icons/favorites.png"
                    }
                }
            }
        }

        ActivityIndicator {
            id: activity
            running: true
            z: 2
            x: (writeTwit.width / 2) - (activity.width / 2)
            visible: true
        }

        TwitLine {
            width: parent.width
            height: parent.height - activity.y - units.gu(2)
        }
    }

    Component.onCompleted: {
        activity.visible = false;
    }
}
