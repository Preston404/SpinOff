#include "inc/PS_hero.h"
#include <QKeyEvent>
#include <QDebug>


Hero::Hero(int x, int y) : GameCharacter(x,y){
    this->attackRSprite = QPixmap(":images/hero_attacking_right.png");
    this->attackLSprite = QPixmap(":images/hero_attacking_left.png");
    this->moveRSprite = QPixmap(":images/hero_walk_sprites.png");
    this->moveLSprite = QPixmap(":images/hero_walk_sprites_left.png");
    this->stopSprite = QPixmap(":images/hero_idle.png");
    this->rect = QRect(x, y, 45, moveRSprite.height() - 7);
    this->timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_100_ms()));
    this->timer->start(100);

    this->timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(on_10_ms()));
    this->timer2->start(10);


}



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

void Hero::on_100_ms(){
    if(getIsAttacking() && ms_time < 500){
        ms_time += 100;
    }
    else if(getIsAttacking() && ms_time >= 500){
        setIsAttacking(false);
        ms_time += 100;
    }
    else if(ms_time > 500 && ms_time <= 1000){
        ms_time += 100;
        setIsAttacking(false);
    }
    else{
        ms_time = -1;
    }
}

void Hero::on_10_ms()
{
    //test_keys();
}

void Hero::startAttackSword(){
    if(!getIsAttacking() && ms_time == -1){
        QSound::play("grunt_sound.wav");
        setIsAttacking(true);

    }
}


