#include <inc/AA_gameengine.h>
#include "inc/AA_mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <QTimer>
#include "inc/AA_gamemodel.h"
#include <QString>


GameEngine::GameEngine(GameModel *m, QWidget *v) : QObject(){
    //Load the JSON file which contains all the players data
    this->LoadPlayersFile();
    //Link model and viewport with engine
    this->model = m;
    this->viewport = v;
    //active player is 0
    this->ActivePlayer = 0;
    //game is not started yet
    gameStarted = false;
    //Used to apply a smooth landing with right and down arrows, can make jmps shorter or longer
    xRelative = -100;
    yRelative = 0;
    aWinDemoMode = false;
    //used to clac the offset when doing background animation
    iterBackground=0;
}

int EnemyBat::currentFrame = 0;
int Brick::speed = 4;

//----------------------------------------------------------------------------------------------------------------//
GameEngine::~GameEngine(){
    this->SavePlayersFile();
    killTimer(timerId);
}
//----------------------------------------------------------------------------------------------------------------//
//This will be called until the game is stopped
//----------------------------------------------------------------------------------------------------------------//
void GameEngine::timerEvent(QTimerEvent *){
    //Debugging helper
    QString ff = QString::number(this->model->getMapPos());
    //qDebug(QString::number(this->model->getMapPos()).toStdString().c_str());
    QString::number(this->model->getMapPos()).toStdString().c_str();

    if(this->Completed()){
        if(this->ActivePlayer->aLevelToLoad == ":Level_1.txt"){
            this->ActivePlayer->LevelOneCompleted = true;
            this->ActivePlayer->aLevelToLoad = ":Level_2.txt";
        }
        this->stopGame();
        this->model->AnnounceCompleted();
        return;
    }

    movementHero();
    movementBoss();
    getModel()->brickClipping();
    hurted();
    GameOver();
    viewport->repaint();
}
//Stops the game
void GameEngine::stopGame(){
    gameStarted = false;
    if(this->timerId != 0){
        killTimer(this->timerId);
    }
}
//Starts the game
void GameEngine::startGame(){
    gameStarted = true;
    if(this->timerId != 0)  {
        killTimer(this->timerId);
    }
    this->timerId = startTimer(15);
}
//Return true if the gameStarted member is true
bool GameEngine::isStarted()
{
    if(gameStarted == true)
        return true;
    else
        return false;
}
//----------------------------------------------------------------------------------------------------------------//
//The available players who were created previously are loaded and saved to an JSON file
//we call this on the applications start up
void GameEngine::LoadPlayersFile(){
    //Clear the list on start
    this->PlayersList.clear();
    //The file is located next to the application EXE file, its name is "players.json"
    QFile file;
    file.setFileName(qGuiApp->applicationDirPath() + "\\players.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    //Read all contents of the json file in 1 shot
    QByteArray jsonData = file.readAll();
    file.close();
    qDebug() << jsonData;
    //Create a JSON document in memory from the data we read
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    //Access the Array object at the root of the document
    QJsonValue value = object.value("PlayersArray");
    QJsonArray array = value.toArray();
    //Do a loop to read the contents of this array, each element in this array reperesent the infomation of 1 player who
    //used the game
    foreach (const QJsonValue & v, array){
        //Create a new empty player object
        Player *newplayer = new Player();
        //Read the properties of the element in the array and assign it to this new player object
        newplayer->ID =   v.toObject().value("ID").toInt();
        newplayer->Name = v.toObject().value("name").toString();
        newplayer->Score = v.toObject().value("score").toInt();
        newplayer->CurrentLevel = v.toObject().value("currentlevel").toInt();
        newplayer->Password =  v.toObject().value("password").toString();
        //Add this player to the list in the global game engine
        this->PlayersList.append(newplayer);
    }
    qDebug() << "Loaded " << this->PlayersList.count() << " Players";
}
//The available players who were created previously are to be saved to an JSON file
//We call this when a new player is created or when the applications exits
void GameEngine::SavePlayersFile(){

    // The QListIterator constructor takes a QList
    // as argument. After construction, the iterator
    // is located at the very beginning of the list
    // (before the first item)
    QListIterator<Player*> iter(this->PlayersList);

    //Nothing to save !
    if(iter.hasNext() == false){
        return;
    }

    //JSON array to save the elements inside it
    QJsonArray players_array;

    while(iter.hasNext())  {
        // The next() function returns the next item
        // in the list and advances the iterator.
        //Cast the current item as a player to access its properties
        Player* player = iter.next();
        qDebug() << player->Name;
        // use initializer list to construct QJsonObject
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

    QJsonObject obj;//root object in the document
    obj["PlayersArray"] = players_array;
    //CReate a JSON document from the array elements
    QJsonDocument document = QJsonDocument(obj);
    //The file is located next to the application EXE file, its name is "players.json"
    QFile file;
    file.setFileName(qGuiApp->applicationDirPath() + "\\players.json");
    //Open this file in "Over write mode" because we will write the entire list of all players
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        qWarning("Couldn't open save file.");
    }
    file.write(document.toJson());
    file.close();
}
//Check if the player already exists in the list before adding or loading a player
bool GameEngine::PlayerExists(QString name, QString Password){
    // The QListIterator constructor takes a QList
    // as argument. After construction, the iterator
    // is located at the very beginning of the list
    // (before the first item)
    QListIterator<Player*> iter(this->PlayersList);
    //Nothing to check !
    if(iter.hasNext() == false)  {
        return false;
    }

    while(iter.hasNext())    {
        // The next() function returns the next item
        // in the list and advances the iterator.
        //Cast the current item as a player to access its properties
        Player* player = iter.next();
        //Compare ID and name using case insensitive
        if((player->Password.compare(Password, Qt::CaseInsensitive) == 0 ) && (player->Name.compare(name,Qt::CaseInsensitive) == 0 ))
        {
            return true;
        }
    }
    //If we exit the loop without any match then return FALSE
    return false;
}

Player *GameEngine::GetPlayerbyID(int ID){
    // The QListIterator constructor takes a QList
    // as argument. After construction, the iterator
    // is located at the very beginning of the list
    // (before the first item)
    QListIterator<Player*> iter(this->PlayersList);

    //Nothing to check !
    if(iter.hasNext() == false){
        return nullptr;
    }

    while(iter.hasNext()){
        // The next() function returns the next item
        // in the list and advances the iterator.
        //Cast the current item as a player to access its properties
        Player* player = iter.next();
        //Compare ID and name using case insensitive
        if(player->ID == ID ){
            return player;
        }
    }
    //If we exit the loop without any match then return NULL
    return nullptr;
}

Player *GameEngine::GetPlayer(QString Name, QString Password){

    // The QListIterator constructor takes a QList
    // as argument. After construction, the iterator
    // is located at the very beginning of the list
    // (before the first item)
    QListIterator<Player*> iter(this->PlayersList);
    //Nothing to check !
    if(iter.hasNext() == false){
        return nullptr;
    }


    while(iter.hasNext()){
        // The next() function returns the next item
        // in the list and advances the iterator.
        //Cast the current item as a player to access its properties
        Player* player = iter.next();
        //Compare password and name using case insensitive
        if((player->Name.compare(Name, Qt::CaseInsensitive) == 0 ) && (player->Password.compare(Password, Qt::CaseSensitive) == 0) )
        {
            this->ActivePlayer = player;
            return player;
        }

    }
    //If we exit the loop without any match then return NULL
    return nullptr;
}

//----------------------------------------------------------------------------------------------------------------//
//Compute logic for the hero movement
//----------------------------------------------------------------------------------------------------------------//
void GameEngine::movementHero()
{
    int y = model->getHero()->getRect().y();

    if(getIsJumping())
    {
        for(int i=0; i<4; ++i)
        {
            xRelative += 1;
        }

        yRelative=(-0.02*(xRelative*xRelative)+200);
        y = startJumpY-yRelative;
        moveXHero(y);
        model->getHero()->setCurrentFrame(0);
        if(intersectTopHero(0))
        {
            xRelative=0;
            yRelative=0;
            startJumpY=model->getHero()->getRect().y();
            setIsJumping(false);
        }
    }

    if(intersectBottomHero(0))
    {
        xRelative=0;
        yRelative=0;
        startJumpY=model->getHero()->getRect().y();
        setIsJumping(false);
        moveXHero(y);
        //Animation calc for next frame
        if(getIsMovingR() && tempMove == 1)
        {
            for(int i=0; i<57; i++)
            {
                model->getHero()->setCurrentFrame(model->getHero()->getCurrentFrame() + 1);
            }
            if (model->getHero()->getCurrentFrame() >= 1190 )
            {
                model->getHero()->setCurrentFrame(0);
            }
            tempMove = 0;
        }
        else if(getIsMovingR())
        {
            tempMove++;
        }
        else if(getIsMovingL() && tempMove == 1)
        {
            for(int i=0; i<57; i++)
            {
                model->getHero()->setCurrentFrame(model->getHero()->getCurrentFrame() - 1);
            }
            if (model->getHero()->getCurrentFrame() <= 0 )
            {
                model->getHero()->setCurrentFrame(1191);
            }
            tempMove = 0;
        }
        else if(getIsMovingL())
        {
            tempMove++;
        }
        else
        {
            model->getHero()->setCurrentFrame(0);
        }
    }

    if((!intersectBottomHero(0) && !getIsJumping()))
    {
        yRelative=(-0.02*(xRelative*xRelative));
        for(int i=0; i<4; ++i)
        {
            xRelative += 1;
        }
        //xRelatif+=4;
        if(getIsAttacking())
        {
            for(int i=0; i<7; ++i)
            {
                xRelative += 1;
            }
        }
        y = startJumpY-yRelative;
        moveXHero(y);
        model->getHero()->setCurrentFrame(0);
    }

    // Check for intersection with collectible
    for(int i = 0; i< model->getCollectibles()->length(); i++)
    {
        intersectCollectible(i);
    }

    for(int i = 0; i< model->getEnemyBat()->length(); i++)
    {
        if(model->getHero()->attackIntersect(model->getEnemyBat()->at(i)->getRect()) &&
           model->getHero()->getIsAttacking()){
                model->getEnemyBat()->at(i)->setDestroyed(true);
        }
    }

}

void GameEngine::movementBoss()
{
    int len = model->getBossList()->length();
    for(int i = 0; i < len; i++){
        Boss* bossPtr = model->getBossList()->at(i);
        if(bossPtr->getIsHurted()){
            continue;
        }
        if(bossPtr->getRect().x() > 1000){
            if(model->getHero()->getRect().x() < bossPtr->getRect().x()){
                bossPtr->setIsMovingL(true);
                bossPtr->setIsMovingR(false);
            }
            else{
                bossPtr->setIsMovingL(false);
                bossPtr->setIsMovingR(true);
            }
        }
        else{
            if(model->getHero()->getRect().x() < bossPtr->getRect().x() &&
               bossPtr->attackIntersect(model->getHero()->getRect())){
                bossPtr->setIsMovingL(true);
                bossPtr->setIsMovingR(false);
            }
            else if(bossPtr->attackIntersect(model->getHero()->getRect())){
                bossPtr->setIsMovingL(false);
                bossPtr->setIsMovingR(true);
            }
            else{
                bossPtr->setIsMovingL(false);
                bossPtr->setIsMovingR(false);
            }
        }
        if(bossPtr->getIsMovingR() && !intersectRightBoss(0, bossPtr)){
            moveXBoss(bossPtr->getRect().y(), bossPtr);
        }
        else if(bossPtr->getIsMovingL() && !intersectLeftBoss(0,bossPtr)){
            moveXBoss(bossPtr->getRect().y(), bossPtr);
        }
        // Running Animation
        if(bossPtr->getIsMovingR() && bossPtr->tempMove == 1)
        {
            for(int i=0; i<57; i++)
            {
                bossPtr->setCurrentFrame(bossPtr->getCurrentFrame() + 1);
            }
            if (bossPtr->getCurrentFrame() >= 1190 )
            {
                bossPtr->setCurrentFrame(0);
            }
            bossPtr->tempMove = 0;
        }
        else if(bossPtr->getIsMovingR())
        {
            bossPtr->tempMove++;
        }
        else if(bossPtr->getIsMovingL() && bossPtr->tempMove == 1)
        {
            for(int i=0; i<57; i++)
            {
                bossPtr->setCurrentFrame(bossPtr->getCurrentFrame() - 1);
            }
            if (bossPtr->getCurrentFrame() <= 0 )
            {
                bossPtr->setCurrentFrame(1191);
            }
            bossPtr->tempMove = 0;
        }
        else if(bossPtr->getIsMovingL())
        {
            bossPtr->tempMove++;
        }
    }


}


void GameEngine::moveBrick(int x,Brick * b)
{
    int speed;
    if(moveMap )
        speed=Brick::speed ;
    else
        speed = 0;


    if(intersectBottomBrick(b))
    {
        if(b->getMoveX())
        {
            b->move(x-speed+2, b->getRect().y());
            if(intersectRightBrick(b))
            {
                b->setMoveX(false);
            }
        }
        else if(!b->getMoveX())
        {
            b->move(x-speed-2, b->getRect().y());
            if( intersectLeftBrick(b) || b->getRect().x()<3)
            {
                b->setMoveX(true);
            }
        }
        b->setYR(0);
        b->setXR(0);
        b->setStartY(b->getRect().y());
    }
    else
    {
        b->setYR(-0.02*(b->getXR()*b->getXR()));
        b->setXR(b->getXR()+3);
        int y = b->getStartY() - b->getYR();
        if(b->getMoveX())
        {
            b->move(x-speed+2, y);
            if(intersectRightBrick(b))
                b->setMoveX(false);
        }
        else if(!b->getMoveX())
        {
            b->move(x-speed-2,y);
            if( intersectLeftBrick(b))
            {
                b->setMoveX(true);
            }
        }
    }
}

void GameEngine::moveXHero(int y)
{
    int x=model->getHero()->getRect().x();

    if(!intersectLeftHero(0) && model->getHero()->getRect().x()>=2 && getIsMovingL() )
        x -= Brick::speed;
    else if( !intersectRightHero(0) && model->getHero()->getRect().x()<=350  && getIsMovingR())
        x += Brick::speed;
    if( !intersectRightHero(0) && model->getHero()->getRect().x()>=350  && getIsMovingR() ) {
        moveMap=true;
    }
    else
        moveMap=false;
    model->getHero()->move(x,y);
}

void GameEngine::moveXBoss(int y, Boss* b)
{
    int x = b->getRect().x();

    if(!intersectLeftBoss(0, b) && b->getIsMovingL() ){
        x -= (Brick::speed * 2) / 4;
    }
    else if( !intersectRightBoss(0, b) && b->getIsMovingR()){
        x += (Brick::speed * 2) / 4;
    }
    b->move(x,y);
}
//----------------------------------------------------------------------------------------------------------------//
bool GameEngine::intersectTopHero(int i)
{
    // Recursively Check each possible item to be intersected with
    if(i<model->getFloors()->size() || i < model->getCollectibles()->size())
    {
        if(!model->getFloors()->empty() && i<model->getFloors()->size())
        {
            if(model->getHero()->intersectTop(model->getFloors()->at(i)->getRect()))
                return true;
        }
        intersectTopHero(i+1);
    }
    else
        return false;
}
bool GameEngine::intersectBottomHero(int i)
{
    // Recursively Check each possible item to be intersected with
    if(i<model->getFloors()->size()
    || i<model->getEnemyBat()->size())
    {
        if(!model->getFloors()->empty() && i<model->getFloors()->size())
        {
            if(model->getHero()->intersectBottom(model->getFloors()->at(i)->getRect()))
                return true;
        }
        if(!model->getEnemyBat()->empty() && i<model->getEnemyBat()->size())
        {
            if(model->getHero()->intersectBottom(model->getEnemyBat()->at(i)->getRect()) ) {
                intersectYBatEnemy(i);
                return true;
            }
        }
        intersectBottomHero(i+1);
    }
    else
        return false;
}
bool GameEngine::intersectLeftHero(int i)
{
    // Recursively Check each possible item to be intersected with
    if(i<model->getFloors()->size() || i<model->getEnemyBat()->size())
    {
        if(!model->getFloors()->empty() && i<model->getFloors()->size())
        {
            if(model->getHero()->intersectLeft(model->getFloors()->at(i)->getRect()))
                return true;
        }
        if(!model->getEnemyBat()->empty() && i<model->getEnemyBat()->size())
        {
            if( model->getHero()->intersectLeft(model->getEnemyBat()->at(i)->getRect()) )
                return true;
        }
        intersectLeftHero(i+1);
    }
    else
        return false;
}
bool GameEngine::intersectRightHero(int i)
{
    // Recursively Check each possible item to be intersected with
    if(i<model->getFloors()->size() || i<model->getEnemyBat()->size())
    {
        if(!model->getFloors()->empty() && i<model->getFloors()->size() )
        {
            if(model->getHero()->intersectRight(model->getFloors()->at(i)->getRect()))
                return true;
        }
        if(!model->getEnemyBat()->empty() && i<model->getEnemyBat()->size())
        {
            if(model->getHero()->intersectRight(model->getEnemyBat()->at(i)->getRect()) )
                return true;
        }
        intersectRightHero(i+1);
    }
    else
        return false;
}


bool GameEngine::intersectLeftBoss(int i, Boss* b)
{
    // Recursively Check each possible item to be intersected with
    if(i<model->getFloors()->size() || i<model->getEnemyBat()->size() || i<model->getBossList()->size())
    {
        if(!model->getFloors()->empty() && i<model->getFloors()->size())
        {
            if(b->intersectLeft(model->getFloors()->at(i)->getRect()) &&
                    model->getFloors()->at(i)->getRect().top() > b->getRectPtr()->bottom() + 25)
                return true;
        }
        if(!model->getBossList()->empty() && i<model->getBossList()->size())
        {
            if(b->intersectLeft(model->getBossList()->at(i)->getRect()) && !model->getBossList()->at(i)->getIsHurted())
                return true;
        }
        if(b->intersectLeft(model->getHero()->getRect())){
            b->startAttackSword();
            if(!model->getHero()->getIsAttacking() && !b->getIsHurted()){
                if(aWinDemoMode == true){
                    b->decrementHealth();
                    return true;
                }
                else{
                    model->getHero()->setIsHurted(true);
                }
            }
            else{
                if(!b->getHitCoolDown()){
                    b->decrementHealth();
                }
                //b->setIsHurted(true);
            }
            return true;
        }

        intersectLeftBoss(i+1, b);
    }
    else
        return false;
}

bool GameEngine::intersectRightBoss(int i, Boss* b)
{
    // Recursively Check each possible item to be intersected with
    if(i<model->getFloors()->size() || i<model->getEnemyBat()->size() || i<model->getBossList()->size())
    {
        if(!model->getFloors()->empty() && i<model->getFloors()->size() )
        {
            if(b->intersectRight(model->getFloors()->at(i)->getRect()) &&
                    model->getFloors()->at(i)->getRect().top() > b->getRectPtr()->bottom() + 25)
                return true;
        }
        if(!model->getBossList()->empty() && i<model->getBossList()->size())
        {
            if(b->intersectRight(model->getBossList()->at(i)->getRect()) && !model->getBossList()->at(i)->getIsHurted())
                return true;
        }
        if(b->intersectRight(model->getHero()->getRect())){
            b->startAttackSword();
            if(!model->getHero()->getIsAttacking() && !b->getIsHurted()){
                if(aWinDemoMode == true){
                    b->decrementHealth();
                    return true;
                }
                else{
                    model->getHero()->setIsHurted(true);
                }
            }
            else{
                if(!b->getHitCoolDown()){
                    b->decrementHealth();
                }
                //b->setIsHurted(true);
            }
            return true;
        }

        intersectLeftBoss(i+1, b);
        intersectRightBoss(i+1, b);
    }
    else
        return false;
}


void GameEngine::intersectXBatEnemy(int i)
{
    if(!model->getEnemyBat()->at(i)->isDestroyed() &&
          (model->getEnemyBat()->at(i)->intersectRight(model->getHero()->getRect()) ||
           model->getEnemyBat()->at(i)->intersectLeft(model->getHero()->getRect()) ))
    {

        if(!model->getHero()->getIsMovingR() &&
           !model->getHero()->getIsMovingL() )
        {
            model->getEnemyBat()->at(i)->setMoveX(!model->getEnemyBat()->at(i)->getMoveX());
        }
        if(getModel()->getHero()->getIsMovingR() &&
           !model->getEnemyBat()->at(i)->getMoveX())
        {
            model->getEnemyBat()->at(i)->setMoveX(!model->getEnemyBat()->at(i)->getMoveX());
        }
        else if(getModel()->getHero()->getIsMovingL() &&
                model->getEnemyBat()->at(i)->getMoveX())
        {
            model->getEnemyBat()->at(i)->setMoveX(!model->getEnemyBat()->at(i)->getMoveX());
        }
        // Kill bat with sword attack
#ifdef TEST_KEYS
        model->getEnemyBat()->at(i)->setDestroyed(true);
        return;
#else
        if(model->getHero()->getIsAttacking()){
            model->getEnemyBat()->at(i)->setDestroyed(true);
            return;
        }
#endif
        if(aWinDemoMode == true){
            model->getEnemyBat()->at(i)->setDestroyed(true);
            return;
        }
        else{
            model->getEnemyBat()->at(i)->setDestroyed(true);
            return;
        }
        this->model->getHero()->setIsHurted(true);
    }



}

void GameEngine::intersectYBatEnemy(int i){
    if(!getModel()->getHero()->getIsMovingL()
            && !getModel()->getHero()->getIsMovingR()
            && !model->getEnemyBat()->at(i)->isDestroyed()) {
        getModel()->getHero()->move(getModel()->getEnemyBat()->at(i)->getRect().x(), getModel()->getHero()->getRect().y());
    }
    if(!model->getEnemyBat()->at(i)->isDestroyed() && getIsAttacking())    {
        getModel()->getEnemyBat()->at(i)->setSprite(QString(":images/EnemyBat_die.png"));
        model->getEnemyBat()->at(i)->setDestroyed(true);
    }
    else if(!model->getEnemyBat()->at(i)->isDestroyed() && !getIsAttacking()){
        if(aWinDemoMode == true){
            model->getEnemyBat()->at(i)->setDestroyed(true);
        }
        else{
            this->model->getHero()->setIsHurted(true);
        }
    }
}

void GameEngine::intersectCollectible(int i){
    if(!model->getCollectibles()->at(i)->isDestroyed() &&
          (model->getCollectibles()->at(i)->intersectRight(model->getHero()->getRect()) ||
           model->getCollectibles()->at(i)->intersectLeft(model->getHero()->getRect())))
    {
        model->getCollectibles()->removeAt(i);
    }
}

bool GameEngine::intersectBottomBrick(Brick * m){
    for(int i = 0; i<model->getFloors()->size(); i++) {
        if(m->intersectBottom(model->getFloors()->at(i)->getRect()))
            return true;   }
    return false;
}

bool GameEngine::intersectLeftBrick(Brick * m){
    for(int i = 0; i<model->getFloors()->size(); i++) {
        if(m->intersectLeft(model->getFloors()->at(i)->getRect()))
            return true;   }
    return false;
}

bool GameEngine::intersectRightBrick(Brick * m){
    for(int i = 0; i<model->getFloors()->size(); i++) {
        if(m->intersectRight(model->getFloors()->at(i)->getRect()))
            return true;   }
    return false;
}


void GameEngine::BatEnemyAnim(int i){
    if(tempEnemyBat == 15)
    {
        EnemyBat::currentFrame += 52;
        if (EnemyBat::currentFrame >= 156)
            EnemyBat::currentFrame = 1;
        tempEnemyBat = 0;
    }
    else
        tempEnemyBat++;
    int x=model->getEnemyBat()->at(i)->getRect().x();
    if(!model->getEnemyBat()->at(i)->isDestroyed())
    {
        moveBrick(x,model->getEnemyBat()->at(i));
        intersectXBatEnemy(i);
        if(model->getEnemyBat()->at(i)->getMoveX())
            getModel()->getEnemyBat()->at(i)->setSprite(QString(":images/EnemyBat_right.png"));
        else
            getModel()->getEnemyBat()->at(i)->setSprite(QString(":images/EnemyBat.png"));
        model->getEnemyBat()->at(i)->setSrcRect(QRect(EnemyBat::currentFrame, 0, model->getEnemyBat()->at(i)->getRect().width(), model->getEnemyBat()->at(i)->getRect().height()));
    }
    else {
        model->getEnemyBat()->at(i)->setSrcRect(QRect(0, 0, model->getEnemyBat()->at(i)->getRect().width(), model->getEnemyBat()->at(i)->getRect().height()));

    }
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

void GameEngine::hurted(){
    if(model->getHero()->getIsHurted()) {
        this->stopGame();
        model->getHero()->setLife(0);
        QMessageBox *Msgbox = new QMessageBox();
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setText("Game Over !");
        Msgbox->exec();
        delete Msgbox;
        this->GameOver();
    }
}

bool GameEngine::GameOver() {
    if(getModel()->getHero()->getLife() == 0 || getModel()->getHero()->getRect().y() > 500) {
        //qDebug("Game OVER");
        return true;  }
    else
        return false;
}

bool GameEngine::Completed() {
    if(this->model->getMapPos()  >= this->model->FloorLimit ) {
        return true;   }
    return false;
}
