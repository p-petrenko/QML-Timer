#include "stopwatch.h"
#include "countdown.h"
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    QQmlContext* context = view.engine()->rootContext();

    Stopwatch stopwatch;
    context->setContextProperty("_stopwatch", &stopwatch);

    Countdown countdown;
    context->setContextProperty("_countdown", &countdown);

    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
