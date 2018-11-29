#include "inc/PS_enemybat.h"
#include <QDebug>

EnemyBat::EnemyBat(int x, int y) : Brick(x,y){
    this->setSprite(QString(":images/EnemyBat.png"));
    this->rect = QRect(x, y+5, getSprite().width()/3, getSprite().height());
}

EnemyBat::~EnemyBat() {
    qDebug("Enemy Bat deleted");
}

EnemyBat* EnemyBat::clone(int x, int y){
    EnemyBat* b = new EnemyBat(x, y);
    return b;
};
