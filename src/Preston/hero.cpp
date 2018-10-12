#include "inc/PS_hero.h"
#include <QDebug>

Hero::Hero(int x, int y ) : GameCharacter(x,y){
    this->moveRSprite = QPixmap(":images/hero_walk_sprites.png");
    this->moveLSprite = QPixmap(":images/hero_walk_sprites_left.png");
    this->stopSprite = QPixmap(":images/hero_idle.png");
    this->rect = QRect(x, y, 45, moveRSprite.height() - 7);
}

Hero::~Hero(){    qDebug("Hero deleted\n"); }


bool Hero::intersectTop(QRect r){
    if(r.intersected(getRect()).width() > 7 && getRect().y() > r.y()){
        move(getRect().x(),r.y() + 49);
        return true;   }
    return false;
}

bool Hero::intersectBottom(QRect r){
    if(r.intersected(getRect()).width() > 5 && getRect().y() < r.y()){
        move(getRect().x(),r.y() - getRect().height() + 1);
        return true;   }
    return false;
}

bool Hero::intersectRight(QRect r){
    if(r.intersected(getRect()).height() > 5 && getRect().x() < r.x() )
        return true;
    return false;
}

bool Hero::intersectLeft(QRect r){
    if(r.intersected(getRect()).height() > 5 && getRect().x() > r.x())
        return true;
    return false;
}

