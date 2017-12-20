import QtQuick 2.6
import QtQuick.Window 2.2
import Qt.labs.settings 1.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Window {
    id: window
    visible: true
    width: 400
    height: 300
    minimumHeight: height
    maximumHeight: height
    minimumWidth: width
    maximumWidth: width
    title: qsTr("Calculator")


    Component.onCompleted: {
        requestThread.start()
        resultThread.start()
    }

    GridLayout {
        width: parent.width
        columns: 2
        columnSpacing: 5
        rowSpacing: 10

        Rectangle {
            Layout.fillWidth: true
            height: 20
            Text {
                anchors.right: parent.right
                font.bold: true
                text: "Requests queue size: "
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 20
            Text {
                anchors.left: parent.left
                text: requests.size
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 20
            Text {
                anchors.right: parent.right
                font.bold: true
                text: "Results queue size: "
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 20
            Text {
                anchors.left: parent.left
                text: results.size
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 20
            Text {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                font.bold: true
                text: "Timeout(sec):"
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 20
            ComboBox {
                anchors.left: parent.lest
                anchors.verticalCenter: parent.verticalCenter
                model: [ 0, 1, 2, 3, 4, 5 ]
                onActivated: requestThread.setTimeout(index)
            }
        }

        Rectangle {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            color: "red"
            height: childrenRect.height
            Calculator {
                anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Settings {
        property alias x: window.x
        property alias y: window.y
    }
}
