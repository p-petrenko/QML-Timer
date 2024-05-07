import QtQuick 2.15
import QtQuick.Window 2.15

import "Components"

Item {
    width: 1000
    height: 700

    Rectangle {
        id: background
        anchors.fill: parent
        color: "darkslategrey"
    }

    GlowEffectView { anchors.fill: _topView; opacity: _topView.hovered }

    // переключатель таймер-секундомер вверху экрана
    TopView {
        id: _topView
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 20
        }

        // текущий индекс определяется и нажатием в TabBar _topView, и свайпом в SwipeView _swipeView
        currentIndex: _swipeView.currentIndex
    }

    // компонент с экранами таймера и секундомера
    SwipeTimerView {
        id: _swipeView
        width: parent.width
        anchors {
            top: _topView.bottom
            topMargin: 10
            bottom: parent.bottom
        }

        currentIndex: _topView.currentIndex
    }
}
