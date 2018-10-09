#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>
#include <QString>
#include "painthelper.h"


//Base class for many objects in the game, think of it a building unit
class Brick{

    public:
        //in case the derived class is able to move, it will have a speed
        static int speed;
        Brick(int,int );
        Brick(int, int, QString );
        ~Brick();
        //in case the derived class can be destroyed by an action from the hero for example
        bool isDestroyed() {            return destroyed;         }
        //When the object is destroyed
        void setDestroyed(bool d) {     this->destroyed=d;        }

        QRect getRect();
        void setRect(QRect);

        //The image used to draw the derived class
        QImage & getImage();
        void setImage(QString i) {
            image.load(i);
        }

        //Move X,Y
        void move(int,int );
        void moveBrick();
        void accept(PaintHelper *p) {
            p->PaintImage(this);
        }

        //sprites are animation sequences designed in a special way to simulate an animation
        QPixmap getSprite() {
            return sprite;
        }
        void setSprite(QString sprite) {
            this->sprite.load(sprite);
        }

        //Draws the rectangular portion source of the given pixmap into the given target in the paint device.
        QRect getSrcRect() {
            return srcRect;
        }
        void setSrcRect(QRect srcRect) {
            this->srcRect = srcRect;
        }


        //tests for intersection with other objects from different sides
        bool intersectBottom(QRect );
        bool intersectRight(QRect );
        bool intersectLeft(QRect );
        //Does it move on X axis ?
        bool getMoveX() {         return moveX;          }
        void setMoveX(bool mx) {  this->moveX=mx;        }

        //Direction of move on the X axis           -------0+++++++
        void setXR(int x) {       this->xR=x;            }
        //Direction of move on the Y axis
        void setYR(int y) {       this->yR=y;            }
        //initial Direction of move on the Y axis   -------0+++++++
        void setStartY(int s) {   this->startY=s;        }
        int getXR() {             return xR;             }
        int getYR() {             return yR;             }
        //initial Direction of move on the Y axis   -------0+++++++
        int getStartY() {
            return startY;
        }

    private:
        QImage image;
        bool destroyed;
        bool moveX=true;
        int xR=0;
        int yR=0;
        int startY;
    protected:
        QRect rect;
        QPixmap sprite;
        QRect srcRect;

};

#endif // BRICK_H
