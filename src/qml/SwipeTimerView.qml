import QtQuick 2.15
import QtQuick.Controls 2.15
import "Countdown"
import "Stopwatch"

// Swipe View for switch between views

SwipeView {
    id: swipeTimersView

    CountdownView {}

    StopwatchView {}

}
