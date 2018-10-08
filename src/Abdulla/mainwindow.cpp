#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QString>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),  ui(new Ui::MainWindow){
    ui->setupUi(this);
    qGuiApp->installEventFilter(this);
    this->Model = new GameModel();
    this->Engine = new GameEngine(this->Model, ui->widgetV);
}

MainWindow::~MainWindow(){    delete ui;}

void MainWindow::on_pushButton_clicked(){  this->ActivePlayer =
            this->Engine->GetPlayer( "a", "0000");}


void MainWindow::on_action_New_Player_triggered(){

    DialogCreatePlayer *dialog = new DialogCreatePlayer(this);
CreateCode:
    if(dialog->exec() == QDialog::DialogCode::Accepted ){
        bool exists = this->Engine->PlayerExists(dialog->PlayerName, dialog->PlayerPassword);
        if(exists) {
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setText("This name is already taken, try a different name !");
            Msgbox->exec();
            delete Msgbox;
            goto CreateCode;
        }
        else{//don't Exist
            Player *newplayer = new Player();
            QDateTime dt = QDateTime::currentDateTime();
            newplayer->ID = dt.toTime_t();//http://doc.qt.io/archives/qt-4.8/qt.html#TimeSpec-enum
            newplayer->Name = dialog->PlayerName;
            newplayer->Score = 0;
            newplayer->CurrentLevel = 1;
            newplayer->Password =  dialog->PlayerPassword;
            this->Engine-> PlayersList.append(newplayer);//Qlist (A class)
            //Get the player from the list by his unique ID
            this->Engine->ActivePlayer = this->Engine->GetPlayer(dialog->PlayerName, dialog->PlayerPassword);
            //Save the players file to disk
            emit this->Engine->PlayersListUpdated();
        }
    }
    else//User has pressed cancel to dismiss the dialog
    {   qDebug("Cancelled !");  }
    delete dialog;
}


void MainWindow::on_action_Load_Player_triggered(){
    DialogLoadPlayer *dialog = new DialogLoadPlayer(this);
LoadCode:
    if(dialog->exec() == QDialog::DialogCode::Accepted ){
        bool exists = this->Engine->PlayerExists(dialog->PlayerName, dialog->PlayerPassword);
        if(exists){
            this->ActivePlayer = this->Engine->GetPlayer(dialog->PlayerName, dialog->PlayerPassword);
            this->setWindowTitle(this->ActivePlayer->Name);
        }
        else{
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setText("No such player exists !");
            Msgbox->exec();
            delete Msgbox;
            goto LoadCode;
        }
    }
    else//User has pressed cancel to dismiss the dialog
    {  qDebug("Cancelled !");   }
    delete dialog;
}


void MainWindow::on_actionNew_Game_triggered(){
    if(this->ActivePlayer == nullptr){
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


void MainWindow::UpdateFrame(GameEngine* eng){//mored edit to render level while player going left
    QPainter painter(ui->widgetV);
    PaintHelper *pVisitor = new PaintHelper(&painter);
    for(int i = eng->getModel()->getBricksToDraw()->indexOf(eng->getModel()->getBricksToDraw()->first());
        i<eng->getModel()->getBricksToDraw()->size(); i++) {
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

    //Update the hero,,,
    //,,

}

/*
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(!this->Engine->GameOver()) {
        if(event->key() == Qt::Key_Right)
        else if(event->key() == Qt::Key_Left)
		***
		***}
	*****
        else
            event->ignore();
    }
    if (event->key() == Qt::Key_Escape){
        this->Engine->stopGame();
        qApp->exit();
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    //When spirite stops the background render
}
*/
