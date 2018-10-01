#ifndef ParallaxBackground_H
#define ParallaxBackground_H

#include "brick.h"

class ParallaxBackground : public Brick
{
public:
    ParallaxBackground(int, int);
    ~ParallaxBackground();
    void Scroll();
};

#endif

