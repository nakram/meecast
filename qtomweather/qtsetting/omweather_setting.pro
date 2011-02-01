#-------------------------------------------------
#
# Project created by QtCreator 2011-01-27T14:47:03
#
#-------------------------------------------------

QT       += core gui

TARGET = omweather_settings
TEMPLATE = app


SOURCES += main.cpp\
        setting.cpp \
    settingstations.cpp

HEADERS  += setting.h \
    settingstations.h

FORMS    += setting.ui \
    settingstations.ui

QT += sql xml xmlpatterns 

CONFIG(localdebug):DEFINES += LOCALDEBUG

INCLUDEPATH += ../core
LIBS += -L ../core -lomweather-core

#install

target.path = /usr/bin

INSTALLS += target