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
    // Singleton Pattern Implementation
    static Hero* instance;
    Hero(int, int);

    // Class members used for sword attack
    QTimer* timer;
    int ms_time;

    // This variable is set to true when the player loses
    bool isHurted = false;

public:
    ~Hero(){}

    // Singleton Functions
    static Hero* getInstance(int, int);
    static Hero* getInstance();

    bool intersectTop(QRect );
    bool intersectBottom(QRect );
    bool intersectRight(QRect );
    bool intersectLeft(QRect );

    bool getIsHurted(){
        return isHurted;
    }
    void setIsHurted(bool hurt){
        this->isHurted = hurt;
    }

    void startAttackSword();

    // Function used to implement prototype pattern
    static Hero* clone(int x, int y);

    // Variable used for animation timing
    int tempMove = 0;


public slots:
    // Slot used for attack timing, updates every 100 milliseconds
    void on_100_ms();
};

#endif


