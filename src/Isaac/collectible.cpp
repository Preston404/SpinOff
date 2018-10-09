#include "inc/Isaac/collectible.h"
#include <QDebug>

collectible::collectible(int x, int y, QString p) : Brick(x,y,p){
    rect.setSize(QSize(25,25));
}

collectible::~collectible() {
    qDebug("collectible removed from scene");
}
