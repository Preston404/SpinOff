#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QWidget>
#include <QObject>

#include "inc/IR_floor.h"
#include "inc/PS_hero.h"
#include "inc/AA_gamemodel.h"

#include <QtGlobal>
#include <QObject>
#include <QList>
#include "inc/BL_player.h"
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

    //--------------------------------------------------------------
    //Funations and Procedures
    //--------------------------------------------------------------
    //The list of players that we will load from the JSON file containing the players of this game
    void LoadPlayersFile();
    //Check if the player already exists in the list before adding or loading a player
    bool PlayerExists(QString name, QString Password);
    //Get a player from the list by ID
    Player* GetPlayerbyID(int ID);
    //Returns true if gameStarted is true
    bool isStarted();
    //Get a player from the list by name and password
    Player* GetPlayer(QString Name, QString Password);
    //Stops the game
    void stopGame();
    //Starts the game
    void startGame();
    //Computation and logic for the Hero movement during the game, called on each update of the game frames
    void movementHero();
    void movementBoss();
    //Move the character on the X axis, Right or Left, here we decide how much percentage !
    void moveXHero(int );
    void moveXBoss(int , Boss* );
    void moveBrick(int,Brick *);
    //Is the game over or NOT ?
    bool GameOver();
    //Is the level completed or not ?
    bool Completed();
    //Did the hero get hurted by an enemy ?
    void hurted();

    bool intersectBottomHero(int );
    bool intersectTopHero(int );
    bool intersectRightHero(int );
    bool intersectLeftHero(int );
    void intersectGoldHero(int );

    bool intersectRightBoss(int, Boss* );
    bool intersectLeftBoss(int, Boss* );

    void intersectYBatEnemy(int );
    void intersectXBatEnemy(int );

    void intersectCollectible(int i);

    bool intersectBottomBrick(Brick *);
    bool intersectRightBrick(Brick *);
    bool intersectLeftBrick(Brick *);

    void BatEnemyAnim(int );
    void BackgroundAnim(int );

    inline bool getIsMovingR() {
        return getModel()->getHero()->getIsMovingR();
    }
    inline bool getIsMovingL() {
        return getModel()->getHero()->getIsMovingL();
    }
    inline bool getIsJumping() {
        return getModel()->getHero()->getIsJumping();
    }
    inline bool getIsAttacking() {
        return getModel()->getHero()->getIsAttacking();
    }
    inline void setIsMovingR(bool is) {
        getModel()->getHero()->setIsMovingR(is);
    }
    inline void setIsMovingL(bool is) {
        getModel()->getHero()->setIsMovingL(is);
    }
    inline void setIsJumping(bool is) {
        getModel()->getHero()->setIsJumping(is);
    }
    inline void setIsAttacking(bool is) {
        getModel()->getHero()->setIsAttacking(is);
    }
    inline void setIsGameOver(bool is) {
        this->isGameOver = is;
    }
    inline bool getIsGameOVer() {
        return isGameOver;
    }
    bool getMoveMap() {
        return moveMap;
    }
    std::tuple<> getAllObjects();
    GameModel *getModel() {
        return this->model;
    }

    inline int getXRelative() {
        return xRelative;
    }
    inline void setXRelative(int x) {
        this->xRelative = x;
    }


    //--------------------------------------------------------------
    //Fields
    //--------------------------------------------------------------

    //The List of all players who we load or save to the JSON file
    QList<Player*> PlayersList;

    //The Current Player using the game
    Player* ActivePlayer;



    //No implementation
signals:
    void PlayersListUpdated();
    //Called when its signal is emitted

public slots:
    //The list of players that we will save to the JSON file containing the players of this game
    void SavePlayersFile();

private:
    void timerEvent(QTimerEvent *event);

    GameModel *model;
    QWidget *viewport;
    bool gameStarted;
    int xRelative;
    int yRelative;
    int startJumpY;
    int iterBackground;
    int tempMove = 0;

    int tempEnemyBat = 0;

    bool isGameOver = false;
    bool moveMap=false;

    int timerId=0;
};
#endif // GAMEENGINE_H
