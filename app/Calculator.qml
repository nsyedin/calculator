import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    id: calc
    property string arg1: ""
    property string arg2: ""
    property string operation: ""
    property bool arg1Active: true

    function add(digit, isOperation) {
        if (!isOperation)
        {
            if (arg1Active)
            {
                arg1 += digit
            }
            else
            {
                arg2 += digit
            }
        }
        else if (operation == "")
        {
            operation = digit
            arg1Active = false;
        }
        else
        {
            //error
        }

        result.text += digit
    }

    function clear() {
        calc.arg1 = ""
        calc.arg2 = ""
        calc.operation = ""
        result.text = ""
        arg1Active = true;
    }

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
                    onButtonPressed: calc.add(text, false)
                }
            }
            Button {
                text: "."; width: 40; height: 20
                onButtonPressed: calc.add(text, false)
            }
            Button {
                text: "C"; width: 40; height: 20
                onButtonPressed: calc.clear()
            }
            Button { text: "+"; width: 40; height: 20
                onButtonPressed: calc.add(text, true)
            }
            Button { text: "-"; width: 40; height: 20
                onButtonPressed: calc.add(text, true)
            }
            Button { text: "*"; width: 40; height: 20
                onButtonPressed: calc.add(text, true)
            }
            Button { text: "/"; width: 40; height: 20
                onButtonPressed: calc.add(text, true)
            }
            Button {
                text: "="
                Layout.columnSpan: 4
                Layout.fillWidth: true
                height: 20
                onButtonPressed: {
                    if (calc.arg1 != "" && calc.arg2 != "" && calc.operation != "")
                    {
                        console.log(calc.arg1 + " " + calc.operation + " " + calc.arg2)
                        requestThread.add(calc.operation, calc.arg1, calc.arg2)
                        calc.clear()
                    }
                }
            }
        }
    }
}
