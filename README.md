# Qt_QML_Android_LED_Control_H-W

1. Run the below command to generate gpiod file 
E:\MyFiles\QT_Projects\Hardware_PWM\gpio_daemon>"C:\Users\Dell\AppData\Local\Android\Sdk\ndk\27.0.12077973\ndk-build.cmd" 
[arm64-v8a] Compile        : gpiod <= gpio_daemon.c 
[arm64-v8a] Compile        : gpiod <= gpio_mmio.c 
[arm64-v8a] Executable     : gpiod 
[arm64-v8a] Install        : gpiod => libs/arm64-v8a/gpiod 
2.Move gpiod file windows to android 
adb push E:\MyFiles\QT_Projects\Hardware_PWM\gpio_daemon\libs\arm64-v8a\gpiod /data/local/tmp/ 
3.Make executable in android turmex apk. 
su -c chmod 755 /data/local/tmp/gpiod 
su -c /data/local/tmp/gpiod & 
