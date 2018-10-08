#ifndef Hero_H
#define Hero_H

#include <QDebug>
#include "gamecharacter.h"

class Hero : public GameCharacter
{
public:

    Hero(int, int);
    ~Hero();

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


private:

    bool isHurted = false;

};

#endif
