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

private:
    static Hero* instance;
    Hero(int, int);

public:
    ~Hero(){}
    static Hero* getInstance(int, int);
    static Hero* getInstance();

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
    QTimer* timer;
    QTimer* timer2;
    int ms_time;
    int tempMove = 0;
    static Hero* clone(int x, int y);


private:
    bool isHurted = false;

public slots:
    void on_100_ms();
    void on_10_ms();

};

#endif
