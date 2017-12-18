import QtQuick 2.0

Item {
    id: item
    property alias text: button.text
    signal buttonPressed(string buttonText)
    Rectangle {
        anchors.fill: parent
        radius: 5
        border.color: "gray"
        color: "steelblue"
        Text {
            id: button
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: item.buttonPressed(button.text)
        }
    }
}
