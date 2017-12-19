import QtQuick 2.6
import QtQuick.Window 2.2
import Qt.labs.settings 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Calculator")

    Calculator {
        anchors.fill: parent
    }

    Settings {
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }
}
