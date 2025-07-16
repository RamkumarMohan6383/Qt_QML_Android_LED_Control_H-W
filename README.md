# Qt_QML_Android_LED_Control_H-W

1 . Run the below command to generate gpiod file 

E:\MyFiles\QT_Projects\Hardware_PWM\gpio_daemon>"C:\Users\Dell\AppData\Local\Android\Sdk\ndk\27.0.12077973\ndk-build.cmd" 

[arm64-v8a] Compile        : gpiod <= gpio_daemon.c 

[arm64-v8a] Compile        : gpiod <= gpio_mmio.c 

[arm64-v8a] Executable     : gpiod 

[arm64-v8a] Install        : gpiod => libs/arm64-v8a/gpiod 

2 . Move gpiod file windows to android 

adb push E:\MyFiles\QT_Projects\Hardware_PWM\gpio_daemon\libs\arm64-v8a\gpiod /data/local/tmp/ 

3 . Make executable in android turmex apk. 

su -c chmod 755 /data/local/tmp/gpiod 

su -c /data/local/tmp/gpiod & 

✅ 1. Check if gpiod exists and is executable

In Termux, run:

ls -l /data/local/tmp/gpiod

Expected output:

-rwxr-xr-x 1 root root ... /data/local/tmp/gpiod

# Auto start get Permission

Write script in Windows 99gpiod.sh
 
#!/system/bin/sh
chmod 755 /data/local/tmp/gpiod
/data/local/tmp/gpiod &


Push the File to Android via ADB
Make sure your device is connected via USB with ADB enabled.

In Command Prompt or PowerShell:

1 . C:\Users\Dell>adb root
restarting adbd as root

2 . C:\Users\Dell>adb remount
Remounted / as RW
Remounted /vendor as RW
Remount succeeded

3 . C:\Users\Dell>adb push D:\99gpiod.sh /data/adb/service.d/99gpiod.sh
D:\99gpiod.sh: 1 file pushed, 0 skipped. 0.0 MB/s (76 bytes in 0.008s)

4 . C:\Users\Dell>adb shell chmod 755 /data/adb/service.d/99gpiod.sh

5 . C:\Users\Dell>adb reboot

After reboot, verify your gpiod process is running:

C:\Users\Dell>adb shell "ps | grep gpiod"
root           776     1   10807280   2944 0                   0 S gpiod

This line confirms that your gpiod daemon is successfully running at boot

🔍 What it means:
root – It's running as root ✅

780 – PID of the process

gpiod – Your native daemon

It's sleeping/waiting (S state), likely polling for messages or doing background work
