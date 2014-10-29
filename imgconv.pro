#-------------------------------------------------
#
# Project created by QtCreator 2014-10-25T10:42:15
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imgconv
TEMPLATE = app

win32 {
    INCLUDEPATH += "C:\Program Files\ImageMagick-6.8.9-Q16\include"
    LIBS += -L"C:\Program Files\ImageMagick-6.8.9-Q16\lib" -lCORE_RL_Magick++_ -lCORE_RL_magick_ -lCORE_RL_wand_
}

macx {
    QMAKE_MAC_SDK = macosx10.10
    INCLUDEPATH += /opt/local/include/ImageMagick-6
    LIBS += -L/opt/local/lib -lMagickCore-6.Q16
    QMAKE_CXXFLAGS += -DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16
    CONFIG += c++11
}

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    image.cpp \
    imagefilter.cpp \
    resizefilter.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    image.h \
    imagefilter.h \
    resizefilter.h

FORMS    += mainwindow.ui \
    dialog.ui
