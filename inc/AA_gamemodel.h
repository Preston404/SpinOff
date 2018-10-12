#ifndef GameModel_H
#define GameModel_H
#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QChar>
#include "inc/IR_parallaxbackground.h"
#include "inc/PS_enemybat.h"
#include "inc/IR_collectible.h"
class Floor;
class Hero;
class Brick;

class GameModel{
public:
    GameModel();
    ~GameModel();
    //Used to build the list of visible bricks in the current viewport limits
    void createBrick(QList<QChar>,int,int );
    //Performs visibility tests to sort out the visible bricks which should be drawn in the current viewport limits
    //More here : https://katyscode.wordpress.com/2013/01/21/2d-platform-games-part-3-scrolling-and-parallax-backgrounds/
    void brickClipping();
    //returns the current hero character
    Hero *getHero() {                            return TheHero;       }
    QList<Brick*> *getBricksToDraw() {           return BricksToDraw;  }
    //List of floor bricks
    QList<Floor*> *getFloors() {                 return floors;        }
    QList<ParallaxBackground*> *getBackground() {return background;    }
    //List of enemies
    QList<EnemyBat*> *getEnemyBat() {            return enemyBat;      }
    QList<collectible*> *getCollectibles() {            return collectibles;      }

    //Announce the end of this level
    void AnnounceCompleted();
    //Game model constants
    static int const brickSize = 50;
    static int const GameViewHeight = 500;
    static int const GameViewWidth = 1000;
    //Number of bricks visible on each line = Width / brickSize = 1000/50 = 20
    static int const NbrBrickVisible = 20;
    int getMapPos();
    int FloorLimit = 0;
private:

    QList<Floor*> *floors;
    QList<Brick*> *BricksToDraw;
    QList<ParallaxBackground*> *background;
    //List of enemy bats
    QList<EnemyBat *> *enemyBat;
    QList<collectible *> *collectibles;
    Hero *TheHero;
    //6 text lines which represent the bricks in the game
    QList<QChar> LINE_a; QList<QChar> LINE_b; QList<QChar> LINE_c;
    QList<QChar> LINE_d; QList<QChar> LINE_e; QList<QChar> LINE_f;
    //As the hero moves from left to right, this will hold the current map offset
    int mapPosition = 7;
};

#endif
