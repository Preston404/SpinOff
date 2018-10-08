#ifndef ParallaxBackground_H
#define ParallaxBackground_H

#include "brick.h"

class ParallaxBackground : public Brick{
public:
    ParallaxBackground(int, int);
    ~ParallaxBackground();
    void Scroll();


};

#endif



/*
 * What's a Tilesprite?

A tilesprite is used to create a single background image that looks like it is
scrolling as the player moves. A tilesprite can be used for a single-screen game or for an extended game world.

However, not just any image will work as a tilesprite.
There are two main criteria: pattern and size.

In order to create a smooth scrolling effect, the tilesprite image must have a pattern
that matches seamlessly across opposite edges — which could be its horizontal edges (left and right),
its vertical edges (top and bottom), or both — depending on which direction(s) your game world is supposed to scroll.

*/

// More info : https://docs.idew.org/video-game/project-references/phaser-coding/tilesprite-scrolling
