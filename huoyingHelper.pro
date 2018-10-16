#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T21:35:31
#
#-------------------------------------------------

QT       += core gui

QT+=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = huoyingHelper
TEMPLATE = app

RC_FILE = icon.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    util/rgbutil.cpp \
    plunder/service/plunderService.cpp \
    plunder/widget/playerInfoForm.cpp\
    plunder/widget/playerNameChangeForm.cpp\
    plunder/dao/fontCodeDao.cpp \
    AutoThread.cpp \
    ThreadMsg.cpp

HEADERS+=  mainwindow.h \
    util/rgbutil.h \
    plunder/service/plunderService.h \
    plunder/widget/playerInfoForm.h \
    plunder/widget/playerNameChangeForm.h \
    plunder/dao/fontCodeDao.h \
    AutoThread.h \
    ThreadMsg.h

FORMS    += mainwindow.ui \
    plunder/widget/playerInfoForm.ui \
    plunder/widget/playerNameChangeForm.ui

RESOURCES += \
    image.qrc



