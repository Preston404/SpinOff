#ifndef EnemyBat_H
#define EnemyBat_H

#include "inc/Isaac/brick.h"

// A simple enemy object derived from the brick class
class EnemyBat : public Brick
{
public:
    EnemyBat(int, int);
    //An enemy can have a sprite animation too, not just a static image
    static int currentFrame; // initial frame is 0
    void accept(PaintHelper *p) {
        p->PaintPixmap(this);
    }
    ~EnemyBat();
};

#endif