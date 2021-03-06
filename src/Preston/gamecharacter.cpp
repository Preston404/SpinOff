#include "inc/PS_gamecharacter.h"
#include "inc/PS_enemybat.h"
#include "inc/PS_hero.h"
#include "inc/PS_boss.h"
#include <QDebug>
#include <QRect>
#include "stdio.h"

GameCharacter::GameCharacter(int x, int y){
    //Set initial values on startup
    rect.translate(x, y);
    dead = false;
    isMovingR=false;
    isMovingL=false;
    isJumping=false;

}


GameCharacter::~GameCharacter(){
    qDebug("Person deleted\n");
}


void GameCharacter::move(int x,int y){
    rect.moveTo(x, y);
}

//Check for intersection with other objects
bool GameCharacter::intersect(QRect r){
    if(r.intersects(getRect()))
        return true;
    else
        return false;
}

//Check to see if the hero is within attacking distance of an enemy
bool GameCharacter::attackIntersect(QRect r)
{
    int top_left_x = 0;
    int top_left_y = 0;
    int bottom_right_x = 0;
    int bottom_right_y = 0;

    QRect attack_range;
    getRect().getCoords(&top_left_x, &top_left_y, &bottom_right_x, &bottom_right_y);
    int x_range = 25;

    QPoint top_left = QPoint(top_left_x - x_range, top_left_y - 50);
    QPoint bottom_right = QPoint(bottom_right_x + x_range, bottom_right_y + 50);

    attack_range.setTopLeft(top_left);
    attack_range.setBottomRight(bottom_right);

    if(r.intersects(attack_range))
    {
        //qDebug("In Attack Range");
        return true;
    }
    else
    {
        return false;
    }
}

Brick* GameCharacter::factory(int x, int y)
{
    return EnemyBat::clone(x,y);
}

GameCharacter* GameCharacter::factory(QString s, int x, int y){
    if(s == (QString) "hero"){
        return Hero::clone(x,y);
    }
    else if(s == (QString) "boss"){
        return Boss::clone(x,y);
    }
    else{
        return nullptr;
    }
}




