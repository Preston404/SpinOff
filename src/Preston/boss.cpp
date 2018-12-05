#include "inc/PS_boss.h"
#include <QKeyEvent>
#include <QDebug>


Boss::Boss(int x, int y) : GameCharacter(x,y){
    this->attackRSprite = QPixmap(":images/hero_attacking_right_shadow.png");
    this->attackLSprite = QPixmap(":images/hero_attacking_left_shadow.png");
    this->moveRSprite = QPixmap(":images/hero_walk_sprites_shadow.png");
    this->moveLSprite = QPixmap(":images/hero_walk_sprites_left_shadow.png");
    this->stopSprite = QPixmap(":images/hero_idle_shadow.png");
    this->rect = QRect(x, y, 45, moveRSprite.height() - 7);
    this->timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_100_ms()));
    this->timer->start(100);

}



bool Boss::intersectTop(QRect r){
    if(r.intersected(getRect()).width() > 7 && getRect().y() > r.y()){
        move(getRect().x(),r.y() + 49);
        return true;   }
    return false;
}

bool Boss::intersectBottom(QRect r){
    if(r.intersected(getRect()).width() > 5 && getRect().y() < r.y()){
        move(getRect().x(),r.y() - getRect().height() + 1);
        return true;   }
    return false;
}

bool Boss::intersectRight(QRect r){
    if(r.intersected(getRect()).height() > 5 && getRect().x() < r.x() )
        return true;
    return false;
}

bool Boss::intersectLeft(QRect r){
    if(r.intersected(getRect()).height() > 5 && getRect().x() > r.x())
        return true;
    return false;
}

void Boss::on_100_ms(){
    if(getIsAttacking() && ms_time < 500){
        ms_time += 100;
    }
    else if(getIsAttacking() && ms_time >= 500){
        setIsAttacking(false);
        ms_time += 100;
        hitCoolDown = false;
    }
    else if(ms_time > 500 && ms_time <= 1000){
        ms_time += 100;
        setIsAttacking(false);
    }
    else{
        ms_time = -1;
    }
}

void Boss::startAttackSword(){
    if(!getIsAttacking() && ms_time == -1){
        setIsAttacking(true);

    }
}

Boss* Boss::clone(int x, int y){
    return new Boss(x,y);
}

//Check to see if the hero is within attacking distance of an enemy
bool Boss::attackIntersect(QRect r)
{
    //qDebug() << QString::number(r.x()) << " "  << QString::number(this->getSrcRect().x());
    int attack_range = 500;
    if(abs(this->getRect().x() - r.x()) < attack_range)
    {
        //qDebug("In Attack Range");
        return true;
    }
    else
    {
        //qDebug("Not In Attack Range");
        return false;
    }
}



