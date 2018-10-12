#include "inc/IR_floor.h"
#include <QDebug>

Floor::Floor(int x, int y, QString picture) : Brick(x,y, picture){
}

Floor::~Floor(){
    qDebug("Floor deleted\n");
}
