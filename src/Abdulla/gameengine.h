#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <QWidget>
#include <QObject>
#include "floor.h"
#include "hero.h"
#include "gamemodel.h"
#include <QtGlobal>
#include <QObject>
#include <QList>
#include <player.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QListIterator>
#include <QList>
#include <QMessageBox>


class GameEngine : public QObject{
    Q_OBJECT
public:
    GameEngine(GameModel *m, QWidget *v);
    ~GameEngine();
    void LoadPlayersFile();
    bool PlayerExists(QString name, QString Password);
    Player* GetPlayerbyID(int ID);
    Player* GetPlayer(QString Name, QString Password);
    void stopGame();
    void startGame();
    void movementHero();
    void moveXHero(int );
    void moveBrick(int,Brick *);
    /*
    bool GameOver();
    bool Completed();
    void hurted();
    bool intersectBottomHero(int i);//added i for warrnings
    bool intersectTopHero(int i);
    bool intersectRightHero(int i);
    bool intersectLeftHero(int i);
    void intersectGoldHero(int i);
    bool intersectBottomBrick(Brick *);
    bool intersectRightBrick(Brick *);
    bool intersectLeftBrick(Brick *);
    */
    void BackgroundAnim(int );

    inline void setIsGameOver(bool is) {     this->isGameOver = is;  }
    inline bool getIsGameOVer() {            return isGameOver;      }
    bool getMoveMap() {                      return moveMap;         }
    GameModel *getModel() {                  return this->model;     }


    std::tuple<> getAllObjects();
    QList<Player*> PlayersList;
    Player* ActivePlayer;

signals:
    void PlayersListUpdated();
public slots:
    void SavePlayersFile();
private:
    //void timerEvent(QTimerEvent *event);
    GameModel *model;
    QWidget *viewport;
    bool gameStarted;
    int iterBackground;
    int tempMove = 0;
    bool isGameOver = false;
    bool moveMap=false;
    //int timerId=0;
};
#endif // GAMEENGINE_H
