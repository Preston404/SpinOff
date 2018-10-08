#include "inc/Isaac/brick.h"
#include <QDebug>


//Create a brick in a specific point at X, Y
Brick::Brick(int x,int y) {
    //initial state is not destroyed
    destroyed = false;
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
    rect.moveTo(rect.left()-Brick::speed, rect.top());
}

//Move the brick to a specific point
void Brick::move(int x,int y){
    rect.moveTo(x, y);
}

//Test for collision from bottom
bool Brick::intersectBottom(QRect r){
    if(r.intersected(getRect()).width() > 5 && getRect().y() < r.y()){
        move(getRect().x(),r.y() - getRect().height() + 1);
        return true;
    }
    return false;
}

//Test for collision from Right
bool Brick::intersectRight(QRect r){
    if(r.intersected(getRect()).height() > 5 && getRect().x() < r.x() )
        return true;
    return false;
}

//Test for collision from Left
bool Brick::intersectLeft(QRect r){
    if(r.intersected(getRect()).height() > 5 && getRect().x() > r.x())
        return true;
    return false;
}
