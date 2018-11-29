#-------------------------------------------------
#
# Project created by QtCreator 2018-09-05T10:31:55
#
#-------------------------------------------------

QT       += core gui
QT       += script
QT       += multimedia

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
    src/Isaac/collectible.cpp \
    src/Dustin/gametesting.cpp \
    src/Preston/boss.cpp \
    src/Dustin/objectpool.cpp \
    src/Dustin/createlevel.cpp

HEADERS += \
        inc/AA_mainwindow.h \
    inc/AA_mainwindow.h \
    inc/BL_player.h \
    inc/BL_dialogloadplayer.h \
    inc/BL_dialogcreateplayer.h \
    inc/IR_brick.h \
    inc/IR_floor.h \
    inc/AA_gameengine.h \
    inc/AA_gamemodel.h \
    inc/IR_parallaxbackground.h \
    inc/PS_gamecharacter.h \
    inc/PS_enemybat.h \
    inc/PS_hero.h \
    inc/IR_painthelper.h \
    inc/IR_collectible.h \
    inc/DP_gametesting.h \
    inc/PS_boss.h \
    inc/DP_objectpool.h \
    inc/DP_createlevel.h

FORMS += \
        inc/Abdulla/mainwindow.ui \
    inc/Baoying/dialogloadplayer.ui \
    inc/Baoying/dialogcreateplayer.ui

RESOURCES += \
    GameRes.qrc

DISTFILES += \
    Level_1.txt \
    Level_1_block_overload.txt \
    Level_1_enemies_overload.txt \
    Level_2.txt \
    Level_1_coin_overload.txt \
    background_8bit.wav \
    grunt_sound.wav \
    Randomly_Generated_Level.txt
