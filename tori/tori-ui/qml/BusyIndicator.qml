import QtQuick 2.0

Image {
     id: busy_indicator
     property bool on: false

     source: "../img/busy.png"; visible: busy_indicator.on
     NumberAnimation on rotation { running: busy_indicator.on; from: 0; to: 360; loops: Animation.Infinite; duration: 1200 }
 }
