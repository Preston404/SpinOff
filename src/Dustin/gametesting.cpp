#include "inc/DP_gametesting.h"
#include "inc/AA_mainwindow.h"
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>
#include <QWidget>
#include <QtScript>
#include <QTimer>


//constructor sets aScriptName
GameTesting::GameTesting(QWidget *parent) : QWidget(parent)
{
}

//Run Loose script
void GameTesting::OnLooseScriptSelected(){
    //checks that there is a new game, if there is not a new game it prints an error
    if(!aMainWindow->Engine->isStarted())
    {
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setGeometry(300, 400, 200, 50);
            Msgbox->setText("Please start a new game before entering Demo Mode !");
            Msgbox->exec();
            delete Msgbox;

    }
    //if there is a new game
    else
    {

        aMainWindow->timer = new QTimer();
        connect(aMainWindow->timer, SIGNAL(timeout()), aMainWindow, SLOT(LooseRun()));
        aMainWindow->timer->start(1);
        QMessageBox *Msgbox = new QMessageBox(this);
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setGeometry(300, 400, 200, 50);
        Msgbox->setText("The Script will start in 15 seconds !");
        Msgbox->exec();
        delete Msgbox;
    }
}
//Run Win script
void GameTesting::OnWinScriptSelected(){
    //checks that there is a new game, if there is not a new game it prints an error
    if(!aMainWindow->Engine->isStarted())
    {
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setGeometry(300, 400, 200, 50);
            Msgbox->setText("Please start a new game before entering Demo Mode !");
            Msgbox->exec();
            delete Msgbox;

    }
    //if there is a new game
    else
    {

        aMainWindow->timer = new QTimer();
        connect(aMainWindow->timer, SIGNAL(timeout()), aMainWindow, SLOT(testKeys()));
        aMainWindow->timer->start(1);
        QMessageBox *Msgbox = new QMessageBox(this);
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setGeometry(300, 400, 200, 50);
        Msgbox->setText("The Script will start in 15 seconds !");
        Msgbox->exec();
        delete Msgbox;

    }
}

//sets the attribut aMainWindow
void GameTesting::SetAMainWindow(MainWindow *mw){
    aMainWindow = mw;
}



