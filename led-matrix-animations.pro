#-------------------------------------------------
#
# Project created by QtCreator 2017-12-06T13:39:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = led-matrix-animations
TEMPLATE = app


SOURCES += main.cpp\
        app.cpp \
    renderarea.cpp \
    animationcanvas.cpp \
    animation.cpp \
    circles.cpp \
    colortest.cpp \
    screen.cpp \
    snowflake.cpp \
    xmastree.cpp \
    freqhistogram.cpp \
    text.cpp

HEADERS  += app.h \
    renderarea.h \
    animationcanvas.h \
    animation.h \
    circles.h \
    colortest.h \
    screen.h \
    snowflake.h \
    xmastree.h \
    freqhistogram.h \
    text.h

INCLUDEPATH += ./matrix/include ./CImg
LIBS +=  -L$$_PRO_FILE_PWD_/matrix/lib -lrgbmatrix -lX11 -lpng
