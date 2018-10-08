#ifndef FLOOR_H
#define FLOOR_H

#include "brick.h"
class Floor : public Brick
{
public:

    //Floor where the hero is moving on
    Floor(int, int, QString);
    ~Floor();

};
#endif // FLOOR_H
