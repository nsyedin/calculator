import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    Rectangle {
        anchors.fill: parent
        color: "blue"
        GridLayout {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 4
            rowSpacing: 10
            columnSpacing: 10

            Rectangle {
                color: "steelblue"
                height: 20
                Layout.columnSpan: 4;
                Layout.fillWidth: true;
                Text {
                    id: result
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    font.bold: true
                }
            }

            Repeater {
                model: 10
                Button {
                    text: index < 9 ? index + 1 : 0
                    width: 40
                    height: 20
                    onButtonPressed: result.text = result.text + buttonText
                }
            }
            Button { text: "."; width: 40; height: 20 }
            Button { text: "C"; width: 40; height: 20 }
            Button { text: "+"; width: 40; height: 20 }
            Button { text: "-"; width: 40; height: 20 }
            Button { text: "*"; width: 40; height: 20 }
            Button { text: "/"; width: 40; height: 20 }
            Button { text: "="; Layout.columnSpan: 4; Layout.fillWidth: true; height: 20 }
        }
    }
}
