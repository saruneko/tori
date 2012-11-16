// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ShadowRectangle {
    id: twit

    width: parent.width
    height: 135
    border.width: 2
    border.color: "#2f3032"
    color: "#26282a"

    property alias username: username.text
    property alias nickname: nickname.text
    property alias image: picture.source
    property alias message: message.text

    Row {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 20
        Image {
            id: picture
            source: "/home/gatox/Pictures/gatox.jpg"
            width: 64
            height: 72
            asynchronous: true
        }
        Column {
            id: twit_content
            spacing: 5
            Row {
                spacing: 5
                Text{
                    id: username
                    text: "Diego Sarmentero"
                    color: "white"
                    font.pointSize: 12
                    font.bold: true
                }
                Text{
                    id: nickname
                    text: "@diegosarmentero"
                    color: "gray"
                    font.pointSize: 10
                }
            }
            Text {
                id: message
                text: "Esto es un twit para la aplicacion Tori, y deberia tener 140 caracteres, asi que: blah blah blah2 blah2 blah3 blah3 y no termina mas esto..."
                wrapMode: Text.WordWrap
                width: twit_content.width
                font.pointSize: 11
                color: "#aaabab"
            }
        }
    }
}
