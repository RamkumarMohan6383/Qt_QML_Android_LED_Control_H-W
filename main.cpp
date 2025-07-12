#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "GpioController/gpiocontroller.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<GpioController>("My.Gpio", 1, 0, "GpioController");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Hardware_PWM", "Main");

    return app.exec();
}
