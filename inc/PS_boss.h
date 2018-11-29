#ifndef BOSS_H
#define BOSS_H

#include <QDebug>
#include <QTimer>
#include "inc/PS_gamecharacter.h"
#include <QObject>
#include <QVariant>
#include <QSound>



class Boss : public QObject, public GameCharacter
{

    Q_OBJECT

public:
    Boss(int, int);
    ~Boss(){}

    bool intersectTop(QRect );
    bool intersectBottom(QRect );
    bool intersectRight(QRect );
    bool intersectLeft(QRect );


    bool getIsHurted() {
        return isHurted;
    }
    void setIsHurted(bool hurt) {
        this->isHurted = hurt;
    }
    bool getHitCoolDown(){return hitCoolDown;}
    void decrementHealth(){
        health -= 1;
        if(health == 0){
            setIsHurted(true);
        }
        hitCoolDown = true;
    }

    void startAttackSword();
    static Boss* clone(int x, int y);

    QTimer* timer;
    QTimer* timer2;
    int ms_time;
    int tempMove = 0;


private:
    bool isHurted = false;
    bool hitCoolDown = false;
    int health = 3;


public slots:
    void on_100_ms();

};



#endif // BOSS_H
