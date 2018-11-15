#include "inc/AA_mainwindow.h"
#include "inc/DP_gametesting.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),  ui(new Ui::MainWindow){
    ui->setupUi(this);
    qGuiApp->installEventFilter(this);
    //Create a new global game engine that will stay alive during the life of this application
    this->Model = new GameModel();
    //Link engine with model and viewport
    this->Engine = new GameEngine(this->Model, ui->widgetV);
    
    QSound* s = new QSound("background_8bit.wav");
    s->setLoops(QSound::Infinite);
    s->play();

    GameTesting g;
    g.SetAMainWindow(this);
    g.CreateDemoMenu(this);

#ifdef TEST_KEYS
    this->timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(testKeys()));
    this->timer->start(1);
#endif

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    //Create a new global game engine that will stay alive during the life of this application
    //this->Model = new GameModel();
    //this->Engine = new GameEngine(this->Model, this->Viewport);
    this->ActivePlayer = this->Engine->GetPlayer( "TopHat", "Hermit");
    //this->Engine->LoadPlayersFile();
    //this->Engine->SavePlayersFile();
}


//New player menu is clicked !
void MainWindow::on_action_New_Player_triggered(){
    //Show the Load player dialog
    DialogCreatePlayer *dialog = new DialogCreatePlayer(this);
CreateCode:
    if(dialog->exec() == QDialog::DialogCode::Accepted ){
        bool exists = this->Engine->PlayerExists(dialog->PlayerName, dialog->PlayerPassword);
        if(exists) {
            qDebug("Name is already taken !");
            //The player is not in the list
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setText("This name is already taken, try a different name !");
            Msgbox->exec();
            delete Msgbox;
            //Try again !
            goto CreateCode;
        }
        else{
            qDebug("New Player is created");
            //Create a new empty player object
            Player *newplayer = new Player();
            //Set the properties of the new player
            QDateTime dt = QDateTime::currentDateTime();
            newplayer->ID = dt.toTime_t();
            newplayer->Name = dialog->PlayerName;
            newplayer->Score = 0;
            newplayer->CurrentLevel = 1;
            newplayer->Password =  dialog->PlayerPassword;
            //Add this player to the list in the global game engine
            this->Engine-> PlayersList.append(newplayer);
            //Get the player from the list by his unique ID
            this->Engine->ActivePlayer = this->Engine->GetPlayer(dialog->PlayerName, dialog->PlayerPassword);
            //Save the players file to disk
            emit this->Engine->PlayersListUpdated();
        }
    }
    else//User has pressed cancel to dismiss the dialog
    {   qDebug("Cancelled !");  }
    //Free memory
    delete dialog;
}


//Load a player profile menu is clicked
void MainWindow::on_action_Load_Player_triggered(){
    //Show the Load player dialog
    DialogLoadPlayer *dialog = new DialogLoadPlayer(this);
LoadCode:
    if(dialog->exec() == QDialog::DialogCode::Accepted ){
        bool exists = this->Engine->PlayerExists(dialog->PlayerName, dialog->PlayerPassword);
        if(exists){
            //Get the player from the list by his unique ID
            this->ActivePlayer = this->Engine->GetPlayer(dialog->PlayerName, dialog->PlayerPassword);
            this->setWindowTitle(this->ActivePlayer->Name);
        }
        else{
            qDebug("No such player !");
            //The player is not in the list
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setText("No such player exists !");
            Msgbox->exec();
            delete Msgbox;
            //Try again !
            goto LoadCode;
        }
    }
    else//User has pressed cancel to dismiss the dialog
    {  qDebug("Cancelled !");   }
    //Free memory
    delete dialog;
}


void MainWindow::on_actionNew_Game_triggered(){
    if(this->ActivePlayer == nullptr){
        //The player is not yet loaded
        QMessageBox *Msgbox = new QMessageBox(this);
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setText("You must load your profile before you can start a game\nOr create a new profile");
        Msgbox->exec();
        delete Msgbox;
    }
    else {
        this->StartNewGame(this->ActivePlayer);
    }
}


void MainWindow::StartNewGame(Player* player){

    if(this->Engine != nullptr){
        this->Engine->stopGame();
        delete this->Engine;
        delete this->Model;
    }
    //Create a new global game engine that will stay alive during the life of this application
    this->Model = new GameModel();
    this->Engine = new GameEngine(this->Model, ui->widgetV);
    this->Engine->ActivePlayer = player;
    this->Engine->startGame();
}


bool MainWindow::eventFilter(QObject* object, QEvent* event) {
    {
        //If the paint event comes from the viewport widget then call Update frame
        if (object == ui->widgetV && event->type() == QEvent::Paint) {
            UpdateFrame(this->Engine);
        }
        return QMainWindow::eventFilter(object, event);
    }
}




void MainWindow::UpdateFrame(GameEngine* eng)
{
    QPainter painter(ui->widgetV);
    PaintHelper *pVisitor = new PaintHelper(&painter);
    for(int i = eng->getModel()->getBricksToDraw()->indexOf(eng->getModel()->getBricksToDraw()->first()); i<eng->getModel()->getBricksToDraw()->size(); i++) {
        if(eng->getMoveMap()) {
            eng->getModel()->getBricksToDraw()->at(i)->moveBrick();
        }
    }
    for(int i = eng->getModel()->getBackground()->indexOf(eng->getModel()->getBackground()->first()); i<eng->getModel()->getBackground()->size(); i++) {
        if(eng->getMoveMap())
            eng->BackgroundAnim(i);
        eng->getModel()->getBackground()->at(i)->accept(pVisitor);
    }
    for(int i = 0; i<eng->getModel()->getFloors()->size(); i++) {
        if(eng->getMoveMap())
            eng->getModel()->getFloors()->at(i)->moveBrick();
        eng->getModel()->getFloors()->at(i)->accept(pVisitor);
    }
    for(int i = 0; i<eng->getModel()->getEnemyBat()->size(); i++) {
        if(eng->getModel()->getEnemyBat()->at(i)->isDestroyed() && eng->getMoveMap())
            eng->getModel()->getEnemyBat()->at(i)->moveBrick();
        eng->BatEnemyAnim(i);
        eng->getModel()->getEnemyBat()->at(i)->accept(pVisitor);
    }
    for(int i = 0; i<eng->getModel()->getCollectibles()->size(); i++) {
        if(eng->getMoveMap())
            eng->getModel()->getCollectibles()->at(i)->moveBrick();
        eng->getModel()->getCollectibles()->at(i)->accept(pVisitor);
    }
    for(int i = 0; i<eng->getModel()->getBossList()->size(); i++) {
        Boss* bossPtr = eng->getModel()->getBossList()->at(i);
        if(bossPtr->getIsHurted()){
            continue;
        }
        if(eng->getMoveMap()){
            QRect* bossRectPtr = bossPtr->getRectPtr();
            bossRectPtr->moveTo(bossRectPtr->left()-Brick::speed, bossRectPtr->top());
        }
        bossPtr->setRect(QRect(bossPtr->getRect().x(), bossPtr->getRect().y(), 45, bossPtr->getMoveRSprite().height() - 7));
        bossPtr->setSrcRect(QRect(bossPtr->getCurrentFrame() + 6, 1, bossPtr->getRect().width(), bossPtr->getRect().height()));
        bossPtr->accept(pVisitor);
    }

    eng->getModel()->getHero()->setRect(QRect(eng->getModel()->getHero()->getRect().x(), eng->getModel()->getHero()->getRect().y(), 45, eng->getModel()->getHero()->getMoveRSprite().height() - 7));
    eng->getModel()->getHero()->setSrcRect(QRect(eng->getModel()->getHero()->getCurrentFrame()+6, 1, eng->getModel()->getHero()->getRect().width(), eng->getModel()->getHero()->getRect().height()));
    eng->getModel()->getHero()->accept(pVisitor);

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(!this->Engine->GameOver()) {
        if(event->key() == Qt::Key_Right)
            this->Engine->setIsMovingR(true);
        else if(event->key() == Qt::Key_Left)
            this->Engine->setIsMovingL(true);
        // Use the key 'a' to attack instead
        //else if(event->key() == Qt::Key_Down && this->Engine->getIsJumping())
        //    this->Engine->setIsAttacking(true);
        else if(event->key() == Qt::Key_A)
        {
            this->Engine->getModel()->getHero()->startAttackSword();
        }
        else if((event->key() == Qt::Key_Space || event->key() == Qt::Key_Up) && this->Engine->intersectBottomHero(0)) {
            this->Engine->setIsJumping(true);
            this->Engine->setXRelative(-100);
        }
        else
            event->ignore();
    }
    //JMP
    if (event->key() == Qt::Key_Escape){
        this->Engine->stopGame();
        qApp->exit();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Right )
        this->Engine->setIsMovingR(false);
    else if(event->key() == Qt::Key_Left )
        this->Engine->setIsMovingL(false);
    else
        event->ignore();
}

void MainWindow::testKeys()
{
    static int counter = 0;
    static bool start = false;
    counter += 1;
    if(counter >= 15000){
        counter = 0;
        start = true;
    }
    if(counter % 10 == 0 && start){
        qDebug("Testing Keys");
    }
    if(start)
    {
        this->Engine->setIsMovingR(true);
        if(this->Engine->getIsJumping()){
            this->Engine->setIsAttacking(true);
        }

        this->Engine->getModel()->getHero()->startAttackSword();

        if(this->Engine->intersectBottomHero(0)) {
            this->Engine->setIsJumping(true);
            this->Engine->setXRelative(-100);
        }
    }
}
void MainWindow::on_actionHelp_triggered(){
    QMessageBox m(this);
    m.setWindowTitle("Help");
    m.setText("  Help");
    m.setInformativeText("Right arrow: move forward.\nLeft arrow: move backward.\nUp arrow + whitespace: jump.\nA: use weapon");
    m.exec();
}
void MainWindow::on_actionManual_triggered(){
    QMessageBox m(this);
    m.setWindowTitle("Manual");
    m.setText("\t User's Manual");
    m.setInformativeText("Description\n"
                         "\nSpinoff is a side scrolling platformer action-adventure "
                         "game developed by QTeam Developers. The evil villain Lowser has conquered the Fungus Kingdom using black magic "
                         "and imprisoned the only person who can break the spell, Princess Leach. You (Dario) must save the kingdom by "
                         "rescuing Princess Leach and breaking Lowser’s spell.\n\n"
                         "How to play\n"
                         "\nMove Left: Left Arrow Key\n"
                         "Move Right: Right Arrow Key\n"
                         "Jump: Space Bar\n"
                         "Sword Attack: ‘A’ Key\n\n"
                         "Goal\n"
                         "\nComplete levels by jumping across platforms and fighting enemies before confronting and defeating the final boss.\n"
                         );
    //m.setIconPixmap(QPixmap("./manual.png"));
    m.show();
    m.exec();
}

