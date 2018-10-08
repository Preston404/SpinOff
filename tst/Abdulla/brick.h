#ifndef BRICK_H
#define BRICK_H
#include <QImage>
#include <QRect>
#include <QString>
#include "painthelper.h"

class Brick{
    public:
        Brick(int,int );
        Brick(int, int, QString );
        ~Brick();

        QRect getRect();
        void setRect(QRect);

        //The image used to draw the derived class
        QImage & getImage();
        void setImage(QString i) {
            image.load(i); }

        //Move X,Y
        void move(int,int );
        void moveBrick();
        void accept(PaintHelper *p) {
            p->PaintImage(this);
        }

        //Draws the rectangular portion source of the given pixmap into the given target in the paint device.
        QRect getSrcRect() {
            return srcRect;
        }
        void setSrcRect(QRect srcRect) {
            this->srcRect = srcRect;
        }

        int getStartY() {
            return startY;
        }

    private:
        QImage image;
        bool destroyed;
        int xR=0;
        int yR=0;
        int startY;
    protected:
        QRect rect;

        QRect srcRect;

};

#endif // BRICK_H

