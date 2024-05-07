import QtQuick 2.15
import QtQuick.Controls 2.15
import "../Components"

Rectangle {

    color: "darkslategrey"

    Column {
        id: timerColumn

        width: parent.width

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 50
            bottom: buttonsRow.top
        }

        spacing: 30

        // Clock text input
        CDInputField {
            id: inputField

            anchors.horizontalCenter: timerColumn.horizontalCenter
        }

        MelodyChoice {
            id: melodyChoice

            anchors.horizontalCenter: timerColumn.horizontalCenter

            title: _countdown.melodyName

            onTitleChanged: {
                console.log("setting melody to ", title);
                _countdown.melodyName = title
            }
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
            title: "Готово"
            enabled: _countdown.isStarted
            onClicked: {
                _countdown.reset();
            }
        }

        ButtonGreen {
            width: 200
            // Старт/Пауза/Продолжить
            enabled: inputField.acceptHr || inputField.acceptMin || inputField.acceptSec
            title: _countdown.isActive ? "Пауза" : (_countdown.isStarted ? "Продолжить" : "Старт")

            onClicked: {
                _countdown.startOrPause([inputField.hr, inputField.min, inputField.sec]);
            }
        }
    }

    CongratulationsScreen {
        anchors.fill:parent
        visible: _countdown.isPlaying
        onPressed: _countdown.stopMelody()
    }
}
