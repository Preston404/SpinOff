#include "inc/PS_hero.h"
#include <QDebug>
#include <QTimer>
#include <QObject>

Hero::Hero(int x, int y ) : GameCharacter(x,y){
    this->moveRSprite = QPixmap(":images/hero_walk_sprites.png");
    this->moveLSprite = QPixmap(":images/hero_walk_sprites_left.png");
    this->stopSprite = QPixmap(":images/hero_idle.png");
    this->rect = QRect(x, y, 45, moveRSprite.height() - 7);
    this->isAttackingSword = false;
    this->timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_100_ms()));
    this->timer->start(100);


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
    ms_time += 100;
    //qDebug("1 second");
    //qDebug() << QVariant(ms_time).toString();
    if(getSwordAttack()){
        qDebug("Attacking");
    }
    else{
        qDebug("Not Attacking");
    }
    if(ms_time >= max_timer_count)
    {
        ms_time = 0;
    }
}

void Hero::startAttackSword(){
    if(!inAttackProcess){
        t_end_attack = ms_time + attack_duration_ms;
        t_end_coolDown = ms_time + attack_duration_ms * 2;
        isCoolingDown = false;
        isAttackingSword = true;
        inAttackProcess = true;
    }
}

bool Hero::getSwordAttack(){
    //qDebug() << QVariant(t_end_attack).toString();
    //qDebug() << QVariant(ms_time).toString();
    //qDebug() << QVariant(isCoolingDown).toString();

    if(t_end_coolDown == -1 && t_end_attack == -1 && !isCoolingDown && !isAttackingSword && !inAttackProcess){
        return false;
    }

    if(!isCoolingDown){ // Attacking
        // Handle Timer rollover
        if(t_end_attack <= max_timer_count){
            if(ms_time >= t_end_attack){
                t_end_attack = -1;
                isAttackingSword = false;
                isCoolingDown = true;
                return false;
            }
            else{
                return true;
            }
        }
        else{
            if(ms_time > max_timer_count/2){
                return true;
            }
            else{
                if(ms_time + max_timer_count >= t_end_attack){
                    t_end_attack = -1;
                    isAttackingSword = false;
                    isCoolingDown = true;
                    return false;
                }
                else{
                    return true;
                }
            }
        }
    }
    else{ // Cool Down
        // Handle Timer rollover
        if(t_end_coolDown <= max_timer_count){
            if(ms_time >= t_end_coolDown){
                t_end_coolDown = -1;
                isCoolingDown = false;
                inAttackProcess = false;
                return false;
            }
        }
        else{
            if(ms_time < max_timer_count/2){
                return false;
            }
            if(ms_time + max_timer_count >= t_end_attack){
                t_end_attack = -1;
                isCoolingDown = false;
                inAttackProcess = false;
                return false;
            }
        }
        return false;
    }
}


