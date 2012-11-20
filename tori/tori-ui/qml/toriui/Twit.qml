// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

ShadowRectangle {
    id: twit

    width: timeline.width
    height: 135
    border.width: 2
    border.color: "#2f3032"
    color: "#26282a"

    Row {
        id: twit_row
        anchors.fill: parent
        anchors.margins: 10
        spacing: 20
        Image {
            id: picture_id
            source: "/home/gatox/Pictures/gatox.jpg"
            width: 64
            height: 72
            asynchronous: true
        }
        Column {
            id: twit_content
            spacing: 5
            width: timeline.width - picture_id.width - twit_row.spacing
            Row {
                spacing: 5
                Text{
                    id: username_id
                    text: username
                    color: "white"
                    font.pointSize: 12
                    font.bold: true
                }
                Text{
                    id: nickname_id
                    text: "@diegosarmentero"
                    color: "gray"
                    font.pointSize: 10
                }
            }
            Text {
                id: message_id
                text: "Esto es un twit para la aplicacion Tori, y deberia tener 140 caracteres, asi que: blah blah blah2 blah2 blah3 blah3 y no termina mas esto..."
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                width: timeline.width - picture_id.width - twit_row.spacing - 10
                font.pointSize: 11
                color: "#aaabab"
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(twit.state == 'Details'){
                twit.state = '';
            }else{
                twit.state = 'Details';
            }
        }
    }

    states: State {
        name: "Details"

        PropertyChanges { target: picture_id; width: 130; height: 130 } // Make picture bigger
        PropertyChanges { target: twit; height: timeline.height / 2 }
    }

    transitions: Transition {
        // Make the state changes smooth
        ParallelAnimation {
            ColorAnimation { property: "color"; duration: 500 }
            NumberAnimation { duration: 300; properties: "x,contentY,height,width" }
        }
    }
}
