#include "inc/Abdulla/gamemodel.h"
#include "inc/Isaac/brick.h"

#include <inc/Preston/hero.h>

#include "inc/Isaac/floor.h"
#include "inc/Preston/enemybat.h"
#include <QDebug>
#include <QMessageBox>

GameModel::GameModel(){
    this->background = new QList<ParallaxBackground *>;
    this->floors = new QList<Floor *>;
    this->enemyBat=new QList<EnemyBat *>;
    this->background = new QList<ParallaxBackground *>;
    this->BricksToDraw = new QList<Brick*> ;
    this->TheHero = new Hero(200, 340);
    QFile LevelFile(":Level_1.txt");
    if(LevelFile.open(QIODevice::ReadOnly)){
        QTextStream in (&LevelFile);
        //Read the level file line by line
        while(!in.atEnd()) {
            QString stock = in.readLine();

            //line starting with a is the bottom level
            if (stock.left(1)=="a")     {
                for(int i=0; i<stock.size(); ++i) {
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()) {
                        LINE_a.append(stock.at(i));
                        FloorLimit++;                      }
                }
            }
            else if (stock.left(1)=="b"){//one level higher than a
                for(int i=0; i<stock.size(); ++i) {
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()) {
                        LINE_b.append(stock.at(i));        }
                }
            }
            else if (stock.left(1)=="c"){//one level higher than b
                for(int i=0; i<stock.size(); ++i) {
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()) {
                        LINE_c.append(stock.at(i));        }
                }
            }
            else if (stock.left(1)=="d") {
                for(int i=0; i<stock.size(); ++i) {
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()) {
                        LINE_d.append(stock.at(i));        }
                }
            }
            else if (stock.left(1)=="e") {
                for(int i=0; i<stock.size(); ++i) {
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()) {
                        LINE_e.append(stock.at(i));        }
                }
            }
            else if (stock.left(1)=="f") {
                for(int i=0; i<stock.size(); ++i) {
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()) {
                        LINE_f.append(stock.at(i));         }
                }
            }
        }
        LevelFile.close();
    }

    //Create the floor bricks
    for (int i=0; i<NbrBrickVisible; i++) {
        Floor *k= new Floor(i*brickSize, GameViewHeight-brickSize, QString(":images/floor_bottom.png"));
        floors->append(k);
        Floor *k2= new Floor(i*brickSize, GameViewHeight-2*brickSize, QString(":images/floor_grass.png"));
        floors->append(k2);         }

    for (int i=0; i<NbrBrickVisible; i++) {
        Brick *b=new Brick(i*brickSize,GameViewHeight+brickSize);
        BricksToDraw->append(b);    }

    //Create the background
    for (int i=0; i<2; i++) {
        ParallaxBackground* b = new ParallaxBackground(i*GameModel::GameViewWidth, 0);
        background->append(b);      }
}

//--------------------------------------------------------------------------------------------------------//

GameModel::~GameModel(){
    floors->clear();
    delete floors;

    BricksToDraw->clear();
    delete BricksToDraw;

    background->clear();
    delete background;

    enemyBat->clear();
    delete enemyBat;

    delete TheHero;
}

//-----------------------------------------------------------------------------------------------------------------//

void GameModel::createBrick(QList<QChar> l,int num,int x) {
    QChar myChar = l.at(mapPosition);

    if(myChar == '0')
        return;
    else if(myChar == '1') {
        Floor *k= new Floor(x+brickSize,GameViewHeight-num*brickSize, QString(":images/floor_bottom.png"));
        floors->append(k);
        return;
    }
    else if(myChar == '4') {
        EnemyBat* d= new EnemyBat(x+brickSize, GameViewHeight-num*brickSize);
        d->setMoveX(false);
        enemyBat->append(d);
        return;
    }
    else if(myChar == '7') {
        Floor *k= new Floor(x+brickSize,GameViewHeight-num*brickSize, QString(":images/floor_grass.png"));
        floors->append(k);
        return;
    }
}

//----------------------------------------------------------------------------------------------------------------//

void GameModel::brickClipping(){
    for(int i = 0; i<background->size(); i++) {
        if(background->at(i)->getRect().x() < - background->at(i)->getRect().width() + 2) {
            background->removeAt(i);
            ParallaxBackground* b = new ParallaxBackground(1000,0);
            background->append(b);
        }
    }
    //As the hero moves from left to right, this code below in the "if" block will
    //be executed to add newly visible bricks
    if(BricksToDraw->last()->getRect().x()<((NbrBrickVisible)*brickSize)) {
        Brick *b=new Brick(BricksToDraw->last()->getRect().x()+brickSize,GameViewHeight+brickSize);
        createBrick(LINE_a,1,BricksToDraw->last()->getRect().x());
        createBrick(LINE_b,2,BricksToDraw->last()->getRect().x());
        createBrick(LINE_c,3,BricksToDraw->last()->getRect().x());
        createBrick(LINE_d,4,BricksToDraw->last()->getRect().x());
        createBrick(LINE_e,5,BricksToDraw->last()->getRect().x());
        createBrick(LINE_f,6,BricksToDraw->last()->getRect().x());
        BricksToDraw->append(b);
        mapPosition++;
    }

    //Remove the bricks on the left of the hero which are no longer visible
    if (BricksToDraw->first()->getRect().x()<=-brickSize) {
        BricksToDraw->removeAt(BricksToDraw->indexOf(BricksToDraw->first()));
    }

    for(int i = 0; i<floors->size(); i++) {
        if (floors->at(i)->getRect().x()<=-brickSize || floors->at(i)->isDestroyed()) {
            floors->removeAt(i);
        }
    }

    for(int i = 0; i<enemyBat->size(); i++) {
        if (enemyBat->at(i)->getRect().x()<=-brickSize ) {
            enemyBat->removeAt(i);
        }
    }
}


void GameModel::AnnounceCompleted() {
    QMessageBox *Msgbox = new QMessageBox();
    Msgbox->setIcon(QMessageBox::Critical);
    Msgbox->setText("END OF LEVEL !");
    Msgbox->exec();
    delete Msgbox;
    qDebug("END OF LEVEL");
}

int GameModel::getMapPos(){
    return this->mapPosition;
}
