#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <QObject>

class GpioController : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE void sendCommand(int cmd, int value);
};

#endif
