#include <gameengine.h>
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <QTimer>
#include "gamemodel.h"
#include <QString>


GameEngine::GameEngine(GameModel *m, QWidget *v) : QObject(){
    this->LoadPlayersFile();
    this->model = m;
    this->viewport = v;
    gameStarted = false;
    iterBackground=0;
}

GameEngine::~GameEngine(){ }
void GameEngine::stopGame() { }
void GameEngine::movementHero(){}

void GameEngine::startGame(){
    gameStarted = true;
    //if(this->timerId != 0)  {    }
    //add here too
}

void GameEngine::LoadPlayersFile(){
    this->PlayersList.clear();
    QFile file;
    file.setFileName(qGuiApp->applicationDirPath() + "\\players.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    QJsonValue value = object.value("PlayersArray");
    QJsonArray array = value.toArray();
    foreach (const QJsonValue & v, array){
        Player *newplayer = new Player();
        newplayer->ID =   v.toObject().value("ID").toInt();
        newplayer->Name = v.toObject().value("name").toString();
        newplayer->Score = v.toObject().value("score").toInt();
        newplayer->CurrentLevel = v.toObject().value("currentlevel").toInt();
        newplayer->Password =  v.toObject().value("password").toString();
        this->PlayersList.append(newplayer);
    }
    qDebug() << "Loaded " << this->PlayersList.count() << " Players";
}

void GameEngine::SavePlayersFile(){
    QListIterator<Player*> iter(this->PlayersList);
    if(iter.hasNext() == false){
        return;
    }
    QJsonArray players_array;
    while(iter.hasNext())  {
        Player* player = iter.next();
        qDebug() << player->Name;
        QJsonObject playerJsonElement = QJsonObject(
        {
            qMakePair(QString("ID"), QJsonValue(player->ID)),
            qMakePair(QString("name"), QJsonValue(player->Name)),
            qMakePair(QString("password"), QJsonValue(player->Password)),
            qMakePair(QString("score"), QJsonValue(player->Score)),
            qMakePair(QString("currentlevel"), QJsonValue(player->CurrentLevel))
        });

        players_array.push_back(QJsonValue(playerJsonElement));

    }

    QJsonObject obj;
    obj["PlayersArray"] = players_array;
    QJsonDocument document = QJsonDocument(obj);
    QFile file;
    file.setFileName(qGuiApp->applicationDirPath() + "\\players.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        qWarning("Couldn't open save file.");
    }
    file.write(document.toJson());
    file.close();
}

bool GameEngine::PlayerExists(QString name, QString Password){
    QListIterator<Player*> iter(this->PlayersList);
    if(iter.hasNext() == false)  {
        return false;
    }

    while(iter.hasNext())    {
        Player* player = iter.next();
        if((player->Password.compare(Password, Qt::CaseInsensitive) == 0 ) && (player->Name.compare(name,Qt::CaseInsensitive) == 0 ))
        {
            return true;
        }
    }
    return false;
}

Player *GameEngine::GetPlayerbyID(int ID){
    QListIterator<Player*> iter(this->PlayersList);
    if(iter.hasNext() == false){
        return nullptr; }

    while(iter.hasNext()){
        Player* player = iter.next();
        if(player->ID == ID ){
            return player;
        }
    }
    return nullptr;
}

Player *GameEngine::GetPlayer(QString Name, QString Password){
    QListIterator<Player*> iter(this->PlayersList);
    if(iter.hasNext() == false){
        return nullptr;
    }
    while(iter.hasNext()){
        Player* player = iter.next();
        if((player->Name.compare(Name, Qt::CaseInsensitive) == 0 ) && (player->Password.compare(Password, Qt::CaseSensitive) == 0) )
        {
            return player;
        }
    }
    return nullptr;// Solve Start game issue
}

void GameEngine::moveBrick(int x,Brick * b){
    //if spirite moving we move
}


void GameEngine::BackgroundAnim(int i){
    if(iterBackground == 2) {
        model->getBackground()->at(i)->Scroll();
        iterBackground=0;
    }
    else {
        iterBackground++;
    }
}



//bool GameEngine::intersectHero(int i)   {   return true;  }
//bool GameEngine::intersectBrick(Brick * m){   return true;   }
//void GameEngine::hurted(){ }
//bool GameEngine::GameOver() {  return false; }
//bool GameEngine::Completed() {  return false;}


