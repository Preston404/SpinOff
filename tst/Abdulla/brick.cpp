#include "brick.h"
#include <QDebug>


//Create a brick in a specific point at X, Y
Brick::Brick(int x,int y) {
    destroyed = false;      //initial state is not destroyed
    rect.translate(x, y);
    rect.setSize(QSize(50,50));
}

//Create a brick using an image from the resources in this app "QRC" file is embedded with the application code
Brick::Brick(int x, int y, QString picture){
    image.load(picture);
    destroyed = false;
    rect = image.rect();
    rect.translate(x, y);
}

Brick::~Brick(){
    qDebug("Brick deleted\n");
}

QRect Brick::getRect(){
    return rect;
}

void Brick::setRect(QRect rct){
    rect = rct;
}

QImage & Brick::getImage(){
    return image;
}

//Move the brick in specifc speed, each time this function is called, the brick is moved
void Brick::moveBrick(){
    rect.moveTo(rect.left(), rect.top());
}

//Move the brick to a specific point
void Brick::move(int x,int y){
    rect.moveTo(x, y);
}

