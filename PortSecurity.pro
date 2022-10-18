#-------------------------------------------------
#
# Project created by QtCreator 2020-06-08T13:59:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PortSecurity
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
OBJECTS_DIR = temp/obj
UI_DIR      = temp/ui
DESTDIR     = bin

#QMAKE_CC += -g
#QMAKE_CXX += -g
#QMAKE_LINK += -g
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"
QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/SDK/lib\'"
QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/SDK/HCNetSDKCom\'"

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        filesystem.cpp \
        maindeal.cpp

HEADERS += \
        mainwindow.h \
        common.h \
        filesystem.h \
        public/Version.h \
        maindeal.h


include("./UI/ui.pri")
include("./LED/led.pri")
include("./SDK/sdk.pri")
include("./MONITOR/monitor.pri")

DISTFILES += \
    UI/ui.pri \
    LED/led.pri \
    SDK/sdk.pri \
    MONITOR/monitor.pri

FORMS += \
     mainwindow.ui


#Eigen
INCLUDEPATH += /usr/include/eigen3


INCLUDEPATH += /usr/local/include/vtk-8.2
LIBS += /usr/local/lib/libvtk*.so

INCLUDEPATH += /usr/local/include/pcl-1.11
LIBS += /usr/local/lib/libpcl_*.so

INCLUDEPATH += $$PWD/.

#Boost
INCLUDEPATH += /usr/local/include/boost/
LIBS += /usr/local/lib/libboost_wave.so
LIBS += /usr/local/lib/libboost_*

INCLUDEPATH += /usr/include/opencv4/
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_*.so

#LIBS += /usr/lib/x86_64-linux-gnu/libboost_*.so
LIBS +=/usr/lib/x86_64-linux-gnu/libalibabacloud-sdk-dysmsapi.so
#LIBS +=/usr/lib/x86_64-linux-gnu/libalibabacloud-sdk-ubsms.so
LIBS +=/usr/lib/x86_64-linux-gnu/libalibabacloud-sdk-core.so

#INCLUDEPATH += /usr/local/include \
#               /usr/local/include/opencv \
#               /usr/local/include/opencv2

#LIBS += /usr/local/lib/libopencv_highgui.so \
#        /usr/local/lib/libopencv_core.so    \
#        /usr/local/lib/libopencv_imgproc.so \
#        /usr/local/lib/libopencv_imgcodecs.so

LIBS += -ldl

RESOURCES += \
    image.qrc

DISTFILES +=

unix:!macx: LIBS += -L$$PWD/SDK/lib/ -lAudioRender
unix:!macx: LIBS += -L$$PWD/SDK/lib/ -lcrypto
unix:!macx: LIBS += -L$$PWD/SDK/lib/ -lHCCore
unix:!macx: LIBS += -L$$PWD/SDK/lib/ -lhcnetsdk
unix:!macx: LIBS += -L$$PWD/SDK/lib/ -lhpr
unix:!macx: LIBS += -L$$PWD/SDK/lib/ -lPlayCtrl
unix:!macx: LIBS += -L$$PWD/SDK/lib/ -lSuperRender
unix:!macx: LIBS += -L$$PWD/SDK/lib/ -lssl

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
QMAKE_LFLAGS += -no-pie #生成可双击打开的可执行文件

RESOURCES += \
    other/qss.qrc \
    other/images.qrc
