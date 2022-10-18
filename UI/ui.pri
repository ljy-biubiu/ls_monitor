SOURCES += \
    $$PWD/src/aboutdialog.cpp \
    $$PWD/src/imageWidget.cpp \
    $$PWD/src/paintarea.cpp \
    $$PWD/src/setroi.cpp \
    $$PWD/src/smsdialog.cpp \
    $$PWD/src/addlidar.cpp \
    $$PWD/src/titlebar.cpp \
    $$PWD/src/maintitlebar.cpp \
    $$PWD/src/childtitlebar.cpp

HEADERS += \
    $$PWD/include/childtitlebar.h \
    $$PWD/include/maintitlebar.h \
    $$PWD/include/aboutdialog.h \
    $$PWD/include/imageWidget.h \
    $$PWD/include/paintarea.h \
    $$PWD/include/setroi.h \
    $$PWD/include/smsdialog.h \
    $$PWD/include/addlidar.h \
    $$PWD/include/titlebar.h

FORMS += \
     $$PWD/forms/aboutdialog.ui \
     $$PWD/forms/setroi.ui \
     $$PWD/forms/smsdialog.ui \
     $$PWD/forms/addpolygon.ui \
     $$PWD/forms/maintitlebar.ui \
     $$PWD/forms/childtitlebar.ui \
     $$PWD/forms/addlidar.ui

INCLUDEPATH += $$PWD/include/.
INCLUDEPATH += $$PWD/src/.
INCLUDEPATH += $$PWD/forms/.
