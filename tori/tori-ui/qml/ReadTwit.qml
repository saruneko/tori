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
                        color: "blue"
        //                source: "../img/reply.png"
        //                fillMode: Image.PreserveAspectFit
                    }
                    ButtonImage{
                        id: retweet
                        width: units.gu(6)
                        height: units.gu(6)
                        image.source: "../img/retweet.png"
        //                fillMode: Image.PreserveAspectFit
                    }
                    ButtonImage{
                        id: favorite
                        width: units.gu(6)
                        height: units.gu(6)
                        color: "yellow"
        //                source: "../img/reply.png"
        //                fillMode: Image.PreserveAspectFit
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
