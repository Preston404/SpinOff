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
    if(e->getIsMovingR()){
        if(e->getIsAttacking()){
            QRect new_rect = e->getRect();
            QPoint new_point = new_rect.bottomRight();
            new_point.setX(new_point.x() + 50);
            new_rect.setBottomRight(new_point);
            getPainter()->drawPixmap(new_rect, e->getAttackRSprite(), e->getAttackRSprite().rect());
            return;
        }
        getPainter()->drawPixmap(e->getRect(), e->getMoveRSprite(), e->getSrcRect());
    }
    else if(e->getIsMovingL()){
        if(e->getIsAttacking()){
            QRect new_rect = e->getRect();
            QPoint new_point = new_rect.bottomLeft();
            new_point.setX(new_point.x() - 50);
            new_rect.setBottomLeft(new_point);
            getPainter()->drawPixmap(new_rect, e->getAttackLSprite(), e->getAttackLSprite().rect());
            return;
        }
        getPainter()->drawPixmap(e->getRect(), e->getMoveLSprite(), e->getSrcRect());
    }
    else{
        if(e->getIsAttacking()){
            QRect new_rect = e->getRect();
            QPoint new_point = new_rect.bottomRight();
            new_point.setX(new_point.x() + 50);
            new_rect.setBottomRight(new_point);
            getPainter()->drawPixmap(new_rect, e->getAttackRSprite(), e->getAttackRSprite().rect());
            return;
        }
        getPainter()->drawPixmap(e->getRect(), e->getStopSprite(), e->getSrcRect());
    }
}

void PaintHelper::PaintPixmap(Brick *e){
        getPainter()->drawPixmap(e->getRect(), e->getSprite(), e->getSrcRect());
}

