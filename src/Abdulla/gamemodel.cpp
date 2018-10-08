#include "gamemodel.h"
#include "brick.h"
#include <floor.h>
#include <QMessageBox>

GameModel::GameModel(){
    this->background = new QList<ParallaxBackground *>;
    this->floors = new QList<Floor *>;
    this->background = new QList<ParallaxBackground *>;
    this->BricksToDraw = new QList<Brick*> ;
    //setup-hero
    QFile LevelFile(":Level_1.txt");//from array Next stage
    if(LevelFile.open(QIODevice::ReadOnly)){
        QTextStream in (&LevelFile);
        while(!in.atEnd()) {
            QString stock = in.readLine();
            if (stock.left(1)=="a")     {            //line starting with a is the bottom level
                for(int i=0; i<stock.size(); ++i) {
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()) {
                        LINE_a.append(stock.at(i));
                       }// FloorLimit++;
                }
            }
            else if (stock.left(1)=="b"){            //one level higher than a
                for(int i=0; i<stock.size(); ++i) {
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()) {
                        LINE_b.append(stock.at(i));        }
                }
            }
            else if (stock.left(1)=="c"){           //one level higher than b
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
        Floor *k2= new Floor(i*brickSize, GameViewHeight-2*brickSize, QString(":images/floor_bottom.png"));
        floors->append(k);
        floors->append(k2);
    }

    for (int i=0; i<NbrBrickVisible; i++) {
        Brick *b=new Brick(i*brickSize,GameViewHeight+brickSize);
        BricksToDraw->append(b);    }
    //Create the background
    for (int i=0; i<2; i++) {
        ParallaxBackground* b = new ParallaxBackground(i*GameModel::GameViewWidth, 0);
        background->append(b);      }
}

GameModel::~GameModel(){
    floors->clear();        delete floors;
    BricksToDraw->clear();  delete BricksToDraw;
    background->clear();    delete background;
}

int GameModel::getMapPos(){
    return this->mapPosition;
}


// void GameModel::AnnounceCompleted() {
//     QMessageBox *Msgbox = new QMessageBox();
//     Msgbox->setIcon(QMessageBox::Critical);
//     Msgbox->setText("END OF LEVEL !");
//     Msgbox->exec();
//     delete Msgbox;
//     qDebug("END OF LEVEL");
// }


/*
void GameModel::brickClipping(){
    //Numbers in above list show up using createBrick(QList<QChar> l,int num,int x)
    //background moving with floors
    //Remove the bricks on the left of the hero which are no longer visible
    //Render As well enimes and more floors
}
*/
