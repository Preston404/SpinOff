#include "inc/IR_painthelper.h"
#include "inc/PS_gamecharacter.h"
#include "inc/IR_brick.h"
#include <QDebug>

PaintHelper::PaintHelper(QPainter *painter){
    this->painter = painter;
}

void PaintHelper::PaintImage(Brick *e){
    getPainter()->drawImage(e->getRect(),e->getImage());
}

void PaintHelper::PaintPixmap(GameCharacter *e){
    if(e->getIsMovingR())
        getPainter()->drawPixmap(e->getRect(), e->getMoveRSprite(), e->getSrcRect());
    else if(e->getIsMovingL())
        getPainter()->drawPixmap(e->getRect(), e->getMoveLSprite(), e->getSrcRect());
    else
        getPainter()->drawPixmap(e->getRect(), e->getStopSprite(), e->getSrcRect());
}

void PaintHelper::PaintPixmap(Brick *e){
        getPainter()->drawPixmap(e->getRect(), e->getSprite(), e->getSrcRect());
}

