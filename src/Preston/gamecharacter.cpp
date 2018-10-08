#include "inc/Preston/gamecharacter.h"
#include <QDebug>
#include <QRect>

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
