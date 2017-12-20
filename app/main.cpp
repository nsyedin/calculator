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

    ThreadSafeQueue<QString> requests;
    ThreadSafeQueue<double> results;

    RequestThread requestThread(requests, results);
    ResultThread resultThread(results);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("requests", &requests);
    engine.rootContext()->setContextProperty("results", &results);
    engine.rootContext()->setContextProperty("requestThread", &requestThread);
    engine.rootContext()->setContextProperty("resultThread", &resultThread);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
