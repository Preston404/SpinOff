#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "inc/Isaac/brick.h"

// A simple enemy object derived from the brick class
class collectible : public Brick
{
public:
    collectible(int, int, QString);
    ~collectible();
};



#endif // COLLECTIBLE_H
