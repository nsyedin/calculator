#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "calc.h"
#include <iostream>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    Error error = Error::NO_ERROR;
    std::cout << calculate(Operation::ADD, 1, 2, error) << std::endl;

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
