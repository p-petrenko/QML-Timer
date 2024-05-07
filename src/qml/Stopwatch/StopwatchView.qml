import QtQuick 2.15
import "../Components"

/*
Упрощенный секундомер, кнопки: старт/стоп и
сброс, кнопка активна только если время не 0
*/

Rectangle {

    property string mainBgColor: "darkslategrey"

    color: mainBgColor

    Rectangle {
        id: clockRectangle

        property int padding: 40;

        implicitWidth: clockTxt.implicitWidth + padding*2
        implicitHeight: clockTxt.implicitHeight + padding

        anchors {
            centerIn: parent
            verticalCenterOffset: -100
        }

        color: 'transparent'
        border.color: 'mistyrose'
        border.width: 3
        radius: 10
        clip: true

        // Clock text
        Text {
            id: clockTxt

            anchors{
                centerIn: parent
                left: parent.left
                right: parent.right
            }

            text: _stopwatch.time
            font.pixelSize: 100
            color: "white"
        }
    }

    // 2 Bottom Buttons
    Row {
        id: buttonsRow

        anchors {
            bottom: parent.bottom
            bottomMargin: 50
            horizontalCenter: parent.horizontalCenter
        }

        spacing: 50

        ButtonGreen {
            width: 200
            title: "Сброс"
            enabled: _stopwatch.isStarted
            onClicked: { _stopwatch.reset() }
        }

        ButtonGreen {
            width: 200
            title: _stopwatch.isActive ? "Стоп" : "Старт"
            onClicked: { _stopwatch.isActive = !_stopwatch.isActive }
        }
    }
}

