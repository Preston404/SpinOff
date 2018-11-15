#include "inc/PS_boss.h"
#include <QKeyEvent>
#include <QDebug>


Boss::Boss(int x, int y) : GameCharacter(x,y){
    this->attackRSprite = QPixmap(":images/hero_attacking_right.png");
    this->attackLSprite = QPixmap(":images/hero_attacking_left.png");
    this->moveRSprite = QPixmap(":images/hero_walk_sprites.png");
    this->moveLSprite = QPixmap(":images/hero_walk_sprites_left.png");
    this->stopSprite = QPixmap(":images/hero_idle.png");
    this->rect = QRect(x, y, 45, moveRSprite.height() - 7);
    this->isAttackingSword = false;
    this->timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_100_ms()));
    this->timer->start(100);

    this->timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(on_50_ms()));
    this->timer2->start(50);


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
    ms_time += 100;
    //qDebug("1 second");
    //qDebug() << QVariant(ms_time).toString();


    if(getSwordAttack()){
        //qDebug("Attacking");
    }
    else{
        //qDebug("Not Attacking");
    }
    if(ms_time >= max_timer_count)
    {
        ms_time = 0;
    }
}

void Boss::on_50_ms()
{
    /*
    action_ms -= 50;
    if(action_ms == max_action_ms * 4){
        setIsMovingL(false);
        setIsMovingR(true);
    }
    if(action_ms == max_action_ms * 3){
        setIsMovingL(false);
        setIsMovingR(false);
    }
    if(action_ms == max_action_ms * 2){
        setIsMovingL(true);
        setIsMovingR(false);
    }
    if(action_ms <= max_action_ms){
        setIsMovingR(false);
        setIsMovingL(false);
    }
    if(action_ms <= 0){
        action_ms = max_action_ms * 5;
    }
    */
}

void Boss::startAttackSword(){
    if(!inAttackProcess){
        QSound::play("grunt_sound.wav");
        setIsAttacking(true);
        t_end_attack = ms_time + attack_duration_ms;
        t_end_coolDown = ms_time + attack_duration_ms * 2;
        isCoolingDown = false;
        isAttackingSword = true;
        inAttackProcess = true;
    }
}

bool Boss::getSwordAttack(){
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
                setIsAttacking(false);
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
                    setIsAttacking(false);
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



