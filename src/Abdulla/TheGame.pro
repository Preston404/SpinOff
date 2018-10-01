#-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T10:31:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheGame
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    player.cpp \
    dialogloadplayer.cpp \
    dialogcreateplayer.cpp \
    brick.cpp \
    floor.cpp \
    gameengine.cpp \
    gamemodel.cpp \
    parallaxbackground.cpp \
    painthelper.cpp

HEADERS += \
        mainwindow.h \
    mainwindow.h \
    player.h \
    dialogloadplayer.h \
    dialogcreateplayer.h \
    brick.h \
    floor.h \
    gameengine.h \
    gamemodel.h \
    parallaxbackground.h \
    painthelper.h

FORMS += \
        mainwindow.ui \
    dialogloadplayer.ui \
    dialogcreateplayer.ui

RESOURCES += \
    GameRes.qrc

DISTFILES +=
