import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Item {
    id: root

    property alias hr: hourTxt.text
    property alias min: minuteTxt.text
    property alias sec: secondTxt.text

    property alias acceptHr: hourTxt.acceptableInput
    property alias acceptMin: minuteTxt.acceptableInput
    property alias acceptSec: secondTxt.acceptableInput

    readonly property string placeholderColor: "light steel blue"
    readonly property string colonColor: "light slate gray"

    width: clockRectangle.width
    height: clockRectangle.height

    Rectangle {
        id: clockRectangle

        width: clockTxtRow.width
        height: clockTxtRow.height

        radius: 10
        clip: true

        color: "#466666" // rgb: 70, 102, 102
    }

    Row {
        id: clockTxtRow

        anchors.centerIn: clockRectangle

        spacing: 0

        // h must be in the range 0 to 23
        TextField {
            id: hourTxt

            leftPadding: 20
            rightPadding: 10

            color: acceptableInput ? "white" : "tomato"
            font.pixelSize: 100
            background: Rectangle { color: 'transparent' }
            focus: true
            validator: IntValidator { top: 23; bottom: 0; }
            overwriteMode: true
            cursorDelegate: CursorComp {}

            Component.onCompleted: {
                hourTxt.cursorPosition = 0
            }

            placeholderText: "00"
            placeholderTextColor: placeholderColor
            text: _countdown.isStarted ? countdown.time[0] : ""

            KeyNavigation.right: minuteTxt
        }

        Text {
            id: colonTxt
            text: ":"
            font.pixelSize: 100
            color: colonColor
        }

        // m and s must be in the range 0 to 59
        TextField {
            id: minuteTxt

            leftPadding: 10
            rightPadding: 10

            color: acceptableInput ? "white" : "tomato"
            font.pixelSize: 100
            background: Rectangle { color: 'transparent' }
            validator: IntValidator { top: 59; bottom: 0; }
            overwriteMode: true
            cursorDelegate: CursorComp {}

            placeholderText: "00"
            placeholderTextColor: placeholderColor
            text: _countdown.isStarted ? _countdown.time[1] : ""

            KeyNavigation.left: hourTxt
            KeyNavigation.right: secondTxt
        }

        Text {
            text: ":"
            font.pixelSize: 100
            color: colonColor
        }

        TextField {
            id: secondTxt

            leftPadding: 10
            rightPadding: 20

            color: acceptableInput ? "white" : "tomato"
            font.pixelSize: 100
            background: Rectangle { color: 'transparent' }
            validator: IntValidator { top: 59; bottom: 0; }
            overwriteMode: true
            cursorDelegate: CursorComp {}
            placeholderText: "00"
            placeholderTextColor: placeholderColor
            text: _countdown.isStarted ? _countdown.time[2] : ""

            KeyNavigation.left: minuteTxt
        }
    }

}
