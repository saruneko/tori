import QtQuick 2.0
import Ubuntu.Components 0.1

Rectangle {
    id: twit
    width: parent.width
    height: units.gu(14)
    border.width: units.dp(1)
    border.color: "#efefef"
    color: "transparent"

    Image {
        id: picture_id
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: units.gu(1)
        anchors.topMargin: units.gu(1)
        source: "../img/gatox_face.png"
        width: units.gu(9)
        height: units.gu(9)
        asynchronous: true
    }
    Rectangle {
        id: imgRounded
        anchors.fill: picture_id
        color: "transparent"
        border.color: main.timeline_background_color // color of background
        border.width: units.gu(0.8)
        radius: units.gu(1)
    }

    Rectangle {
        id: messageArea
        anchors.left: picture_id.right
        anchors.top: parent.top
        anchors.leftMargin: units.gu(1)
        anchors.topMargin: units.gu(1.5)
        width: parent.width - imgRounded.width
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
                width: twit.width - imgRounded.width - units.gu(3)
                fontSize: "medium"
                color: "#323232"
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

            Rectangle{
                id: reply
                width: units.gu(3)
                height: units.gu(3)
                color: "blue"
//                source: "../img/reply.png"
//                fillMode: Image.PreserveAspectFit
                visible: false
            }
            Image{
                id: retweet
                width: units.gu(3)
                height: units.gu(3)
                source: "../img/retweet.png"
                fillMode: Image.PreserveAspectFit
                visible: false
            }
            Rectangle{
                id: favorite
                width: units.gu(3)
                height: units.gu(3)
                color: "yellow"
//                source: "../img/reply.png"
//                fillMode: Image.PreserveAspectFit
                visible: false
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
        }

        onEntered: {
            time.visible = false;
            retweet.visible = true;
            reply.visible = true;
            favorite.visible = true;
            color = "#f0f7f7";
            imgRounded.border.color = "#f0f7f7";
        }
        onExited: {
            time.visible = true;
            color = "transparent";
            imgRounded.border.color = main.timeline_background_color;
            retweet.visible = false;
            reply.visible = false;
            favorite.visible = false;
        }
    }

}
