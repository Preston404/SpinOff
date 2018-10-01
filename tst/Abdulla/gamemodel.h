#ifndef GameModel_H
#define GameModel_H
#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QChar>
#include "parallaxbackground.h"

class Floor;
class Hero;
class Brick;

class GameModel{
public:
    GameModel();
    ~GameModel();
   // void createBrick(QList<QChar>,int,int );
   // void brickClipping();

    Hero          *getHero() {                   return TheHero;       }    //returns the current hero character
    QList<Brick*> *getBricksToDraw() {           return BricksToDraw;  }
    QList<Floor*> *getFloors() {                 return floors;        }    //List of floor bricks
    QList<ParallaxBackground*> *getBackground() {return background;    }
    void AnnounceCompleted();    //Announce the end of this level

    //Game model constants
    static int const brickSize = 50;
    static int const GameViewHeight = 500;
    static int const GameViewWidth = 1000;
    //Number of bricks visible on each line = Width / brickSize = 1000/50 = 20
    static int const NbrBrickVisible = 20;
    int getMapPos();
    //int FloorLimit = 0;
private:
    QList<Floor*> *floors;
    QList<Brick*> *BricksToDraw;
    QList<ParallaxBackground*> *background;
    Hero *TheHero;
    //6 text lines which represent the bricks in the game
    QList<QChar> LINE_a; QList<QChar> LINE_b; QList<QChar> LINE_c;
    QList<QChar> LINE_d; QList<QChar> LINE_e; QList<QChar> LINE_f;
    //As the hero moves from left to right, this will hold the current map offset
    int mapPosition = 7;
};

#endif
