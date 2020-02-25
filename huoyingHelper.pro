#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T21:35:31
#
#-------------------------------------------------

MY_PROJECT_VERSION=1.0

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
    ThreadMsg.cpp \
    PointRepository.cpp \
    PointEntity.cpp \
    common/BaseDao.cpp \
    common/TableViewService.cpp \
    point/PointTableViewService.cpp \
    PointWin.cpp

HEADERS+=  mainwindow.h \
    util/rgbutil.h \
    plunder/service/plunderService.h \
    plunder/widget/playerInfoForm.h \
    plunder/widget/playerNameChangeForm.h \
    plunder/dao/fontCodeDao.h \
    AutoThread.h \
    ThreadMsg.h \
    PointRepository.h \
    PointEntity.h \
    plunder/widget/playerNameChangeForm.cpp.EW8108 \
    common/BaseDao.h \
    point/PointRepository.h \
    common/TableViewService.h \
    point/PointTableViewService.h \
    PointWin.h

FORMS    += mainwindow.ui \
    plunder/widget/playerInfoForm.ui \
    plunder/widget/playerNameChangeForm.ui \
    PointWin.ui

RESOURCES += \
    image.qrc

DISTFILES += \
    icon.ico \
    .gitattributes \
    .gitignore \
    icon.rc \
    README.md \
    common



