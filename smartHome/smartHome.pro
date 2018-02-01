#-------------------------------------------------
#
# Project created by QtCreator 2018-01-18T22:05:24
#
#-------------------------------------------------

QT += core gui
CONFIG += c++11
QT += sql
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smartHome
TEMPLATE = app


SOURCES += main.cpp\
    rotateWidget.cpp \
    signIn.cpp \
    signUp.cpp \
    smartHome.cpp

HEADERS  += \
    rotateWidget.h \
    signIn.h \
    signUp.h \
    smartHome.h

FORMS    += \
    signIn.ui \
    signUp.ui \
    smartHome.ui


RESOURCES += \
    image.qrc

DISTFILES +=


include(./Qwt/qwt.prf)
INCLUDEPATH += "./Qwt/qwt"
