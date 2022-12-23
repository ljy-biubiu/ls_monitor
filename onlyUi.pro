#-------------------------------------------------
#
# Project created by QtCreator 2020-06-08T13:59:38
#
#-------------------------------------------------

QT       += core gui

CONFIG -= qtquickcompiler

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PortMonitor
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
# depend on your compiler). Please consult the JsChatQtation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CFLAGS_ISYSTEM = -I

SOURCES += \
    MSGSERIVE/myparams.h \
    PROTOCOL/include/protocol.hpp \
    src/main.cpp

HEADERS +=  \

include("./UI/ui.pri")

DISTFILES += \
    UI/ui.pri

#Eigen
INCLUDEPATH += /usr/include/eigen3

INCLUDEPATH += /usr/local/include/pcl-1.9
LIBS += /usr/local/lib/libpcl_*.so

INCLUDEPATH += /usr/local/include/vtk-8.2
LIBS += /usr/local/lib/libvtk*.so


INCLUDEPATH += /usr/include/
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_*.so

#Boost
INCLUDEPATH += /usr/include/boost
LIBS += /usr/lib/x86_64-linux-gnu/libboost_*


LIBS += -ldl


INCLUDEPATH += $$PWD/PROTOCOL/include/.
INCLUDEPATH += $$PWD/MSGSERIVE/.
INCLUDEPATH += $$PWD/include/.
DEPENDPATH += $$PWD/.
QMAKE_LFLAGS += -no-pie #生成可双击打开的可执行文件

