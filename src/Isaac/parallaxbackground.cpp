#include "inc/IR_parallaxbackground.h"
#include <QDebug>

ParallaxBackground::ParallaxBackground(int x, int y ) : Brick(x,y, ":images/background.png"){
    this->rect.setSize(QSize(getImage().width()+4,getImage().height()));
}

ParallaxBackground::~ParallaxBackground(){
    qDebug("Background deleted\n");
}

//Move the background image to simulate a scrolling animation
void ParallaxBackground::Scroll(){
    rect.moveTo(rect.left() - Brick::speed/2, rect.top());
}
