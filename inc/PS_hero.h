#ifndef Hero_H
#define Hero_H

#include <QDebug>
#include <QTimer>
#include "inc/PS_gamecharacter.h"
#include <QObject>
#include <QVariant>
#include <QSound>


class Hero : public QObject, public GameCharacter
{

    Q_OBJECT

public:
    Hero(int, int);
    ~Hero(){}

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

    void startAttackSword();

    bool getSwordAttack();

    bool getIsAttackingSword(){
        return isAttackingSword;
    }

    QTimer* timer;
    QTimer* timer2;
    int ms_time;
    int max_timer_count = 10000;
    int attack_duration_ms = 500;
    bool coolDown = false;


private:
    bool inAttackProcess = false;
    int t_end_attack = -1;
    int t = 0;
    bool isHurted = false;
    bool isAttackingSword = false;
    bool isCoolingDown = false;
    int t_end_coolDown = 0;

public slots:
    void on_100_ms();
    void on_10_ms();

};

#endif
