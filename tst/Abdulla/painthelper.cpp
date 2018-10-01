#include "painthelper.h"
#include "brick.h"
#include <QDebug>

PaintHelper::PaintHelper(QPainter *painter){
    this->painter = painter;
}

void PaintHelper::PaintImage(Brick *e){
    getPainter()->drawImage(e->getRect(),e->getImage());
}

void PaintHelper::PaintPixmap(GameCharacter *e){
//spirite Contrall

}

//void PaintHelper::PaintPixmap(Brick *e){
//       spirite thing for later
//}
