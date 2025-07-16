import QtQuick 2.15
import QtQuick.Controls 2.15
import My.Gpio 1.0

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: "74HC595 LED Control"

    GpioController { id: gpio }

   Column {
        anchors.centerIn: parent
        spacing: 10

        /*Repeater {
            model: 7
            delegate: Row {
                spacing: 10

                Text { text: "LED " + index }

                Button {
                    text: "ON"
                    onClicked: gpio.setLedOn(index)
                }

                Button {
                    text: "OFF"
                    onClicked: gpio.setLedOff(index)
                }
            }
        }*/
        Slider {
            id: pwmSlider
            from: 0
            to: 1023
            value: 512
        }

        Button {
            text: "Set PWM"
            onClicked: gpio.sendCommand(4, pwmSlider.value)
        }

        Button {
            text: "Full ON"
            onClicked: gpio.sendCommand(5, 0)
        }

        Button {
            text: "Full OFF"
            onClicked: gpio.sendCommand(6, 0)
        }

        Button {
            text: "LED 50% ON"
            onClicked: gpio.sendCommand(4, 512)  // 50% duty
        }

        Button {
            text: "LED 100% ON"
            onClicked: gpio.sendCommand(4, 1023)  // 50% duty
        }

    }
}
/*import QtQuick 2.15
import QtQuick.Controls 2.15
import My.Gpio 1.0

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "PWM LED"

    GpioController { id: gpio }

    Column {
        anchors.centerIn: parent
        spacing: 15

        Slider {
            id: pwmSlider
            from: 0
            to: 1023
            value: 512
        }

        Button {
            text: "Set PWM"
            onClicked: gpio.sendCommand(4, pwmSlider.value)
        }

        Button {
            text: "Full ON"
            onClicked: gpio.sendCommand(5, 0)
        }

        Button {
            text: "Full OFF"
            onClicked: gpio.sendCommand(6, 0)
        }

        Button {
            text: "LED 50% ON"
            onClicked: gpio.sendCommand(4, 512)  // 50% duty
        }

        Button {
            text: "LED 100% ON"
            onClicked: gpio.sendCommand(4, 1023)  // 50% duty
        }

        Button {
            text: "Pattern 1"
            onClicked: gpio.setLEDPattern(0b00001111)
        }

    }
}
*/
