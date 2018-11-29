#ifndef GameCharacter_H
#define GameCharacter_H

#include <QPixmap>
#include <QImage>
#include <QRect>
#include <QString>
#include "inc/IR_painthelper.h"

//base class for the hero character
class GameCharacter{

public:
    GameCharacter(int, int);
    ~GameCharacter();

    static Brick* factory(int x, int y);
    static GameCharacter* factory(QString s, int x, int y);

    //whether the character is dead or not ?
    bool isDead() {
        return dead;
    }
    void setDead(bool destr) {
        dead = destr;
    }

    //The graphics rectangle representing the character
    QRect getRect() {
        return rect;
    }
    QRect* getRectPtr(){
        return &rect;
    }

    void setSrcRect(QRect srcRect) {
        this->srcRect = srcRect;
    }
    QRect getSrcRect() {
        return srcRect;
    }
    void setRect(QRect rect) {
        this->rect = rect;
    }

    QPixmap getAttackRSprite() {
        return attackRSprite;
    }
    QPixmap getAttackLSprite() {
        return attackLSprite;
    }

    //The rectangle used to represent the sprite of this character when it's moving to the RIGHT
    QPixmap getMoveRSprite() {
        return moveRSprite;
    }
    //The rectangle used to represent the sprite of this character when it's moving to the LEFT
    QPixmap getMoveLSprite() {
        return moveLSprite;
    }
    //The rectangle used to represent the sprite of this character when it's IDLE
    QPixmap getStopSprite() {
        return stopSprite;
    }

    void setMoveRSprite(QString m) {
        moveRSprite.load(m);
    }
    void setMoveLSprite(QString m) {
        moveLSprite.load(m);
    }
    void setStopSprite(QString m) {
        stopSprite.load(m);
    }

    //Is the player moving to the right ?
    bool getIsMovingR() {
        return isMovingR;
    }
    //Is the player moving to the left ?
    bool getIsMovingL() {
        return isMovingL;
    }
    //Is the player jumping now ?
    bool getIsJumping() {
        return isJumping;
    }
    void setIsMovingR(bool is) {
        this->isMovingR = is;
    }
    void setIsMovingL(bool is) {
        this->isMovingL = is;
    }
    void setIsJumping(bool is) {
        this->isJumping = is;
    }
    //Is the player attacking now ?
    bool getIsAttacking() {
        return isAttacking;
    }
    void setIsAttacking(bool is) {
        this->isAttacking = is;
    }

    void startAttackSword(){}
    void setIsHurted(bool b){}
    bool getIsHurted(){return false;}
    bool intersectTop(QRect r){return false;}
    bool intersectBottom(QRect r){return false;}
    bool intersectLeft(QRect r){return false;}
    bool intersectRight(QRect r){return false;}


    void move(int, int);


    //Did the character run out of health ?
    int getLife() {
        return life;
    }
    void setLife(int life) {
        this->life = life;
    }


    bool intersect(QRect );
    bool attack_intersect(QRect );
    void accept(PaintHelper *p) {
        p->PaintPixmap(this);
    }



    //return current frame in the animation
    int getCurrentFrame()
    {
        return currentFrame;
    }
    void setCurrentFrame(int frame) {
        this->currentFrame = frame;
    }

protected:
    QPixmap attackRSprite;
    QPixmap attackLSprite;
    QPixmap moveRSprite;
    QPixmap moveLSprite;
    QPixmap stopSprite;
    QPixmap jumpSprite;
    QRect rect;

    QRect srcRect;
    bool isMovingR;
    bool isMovingL;
    bool isJumping;
    bool isAttacking = false;
    bool dead = false;
    int currentFrame = 0;
private:
    int life = 5;

};

#endif
