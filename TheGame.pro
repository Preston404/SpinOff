#-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T10:31:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/Abdulla/main.cpp \
        src/Abdulla/mainwindow.cpp \
    src/Baoying/player.cpp \
    src/Baoying/dialogloadplayer.cpp \
    src/Baoying/dialogcreateplayer.cpp \
    src/Isaac/brick.cpp \
    src/Isaac/floor.cpp \
    src/Abdulla/gameengine.cpp \
    src/Abdulla/gamemodel.cpp \
    src/Isaac/parallaxbackground.cpp \
    src/Preston/gamecharacter.cpp \
    src/Preston/enemybat.cpp \
    src/Preston/hero.cpp \
    src/Isaac/painthelper.cpp \
    src/Isaac/collectible.cpp

HEADERS += \
        inc/Abdulla/mainwindow.h \
    inc/Abdulla/mainwindow.h \
    inc/Baoying/player.h \
    inc/Baoying/dialogloadplayer.h \
    inc/Baoying/dialogcreateplayer.h \
    inc/Isaac/brick.h \
    inc/Isaac/floor.h \
    inc/Abdulla/gameengine.h \
    inc/Abdulla/gamemodel.h \
    inc/Isaac/parallaxbackground.h \
    inc/Preston/gamecharacter.h \
    inc/Preston/enemybat.h \
    inc/Preston/hero.h \
    inc/Isaac/painthelper.h \
    inc/Isaac/collectible.h

FORMS += \
        inc/Abdulla/mainwindow.ui \
    inc/Baoying/dialogloadplayer.ui \
    inc/Baoying/dialogcreateplayer.ui

RESOURCES += \
    GameRes.qrc

DISTFILES +=
