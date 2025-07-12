cmake_minimum_required(VERSION 3.16)

project(Hardware_PWM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appHardware_PWM
    main.cpp
)

qt_add_qml_module(appHardware_PWM
    URI Hardware_PWM
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES GpioController/gpiocontroller.cpp GpioController/gpiocontroller.h
SOURCES gpio_daemon/jni/gpio_mmio.h
RESOURCES gpio_daemon/jni/Android.mk gpio_daemon/jni/Application.mk gpio_daemon/jni/gpio_daemon.c gpio_daemon/jni/gpio_mmio.c
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appHardware_PWM PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appHardware_PWM
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appHardware_PWM
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appHardware_PWM
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
