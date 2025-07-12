#include "GpioController.h"
#include <QLocalSocket>
#include <QDataStream>

void GpioController::sendCommand(int cmd, int value) {
    QLocalSocket socket;
    socket.connectToServer("/data/local/tmp/gpiod.sock", QIODevice::ReadWrite);
    if (socket.waitForConnected()) {
        QDataStream out(&socket);
        out.setByteOrder(QDataStream::LittleEndian);
        out << cmd << value;
        socket.waitForBytesWritten();
        socket.disconnectFromServer();
    }
}
