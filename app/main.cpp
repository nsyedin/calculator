#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>
#include "requestthread.h"
#include "resultthread.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    ResultThread resultThread;
    RequestThread requestThread(&resultThread);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("requestThread", &requestThread);
    engine.rootContext()->setContextProperty("resultThread", &resultThread);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
