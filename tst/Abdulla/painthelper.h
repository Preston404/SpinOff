#ifndef PaintHelper_H
#define PaintHelper_H
#include <QPainter>
#include <QPaintDevice>
#include <QPaintEngine>

class GameCharacter;
class Brick;

class PaintHelper{
public:
    PaintHelper(QPainter *painter);
    ~PaintHelper();
    void PaintImage(Brick *e);
    void PaintPixmap(Brick *e);
    void PaintPixmap(GameCharacter *e);
    QPainter *getPainter() {
        return painter;
    }

private:
    QPainter *painter;
};

#endif
