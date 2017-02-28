#-------------------------------------------------
#
# Project created by QtCreator 2017-01-11T13:57:25
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoChat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        videochat.cpp \
    video_client.cpp \
    video_server.cpp \
    cg729decoder.cpp \
    cg729encoder.cpp \
    audio_udpthread.cpp \
    audioGet.cpp

HEADERS  += videochat.h \
    video_client.h \
    video_server.h \
    cg729decoder.h \
    cg729encoder.h \
    audio_udpthread.h \
    audioGet.h

FORMS    += videochat.ui

INCLUDEPATH+=$$PWD\include\     \
$$PWD\include\opencv 	\
$$PWD\include\opencv2

LIBS+=$$PWD\lib\va_g729a.lib          \
$$PWD\lib\libopencv_core2411.dll	\
$$PWD\lib\libopencv_imgproc2411.dll	\
$$PWD\lib\libopencv_highgui2411.dll
