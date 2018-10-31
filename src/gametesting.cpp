#include "inc/DP_gametesting.h"
#include "inc/AA_mainwindow.h"
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>
#include <QWidget>
#include <QtScript>


//constructor sets aScriptName
GameTesting::GameTesting(QWidget *parent) : QWidget(parent)
{
    SetAScriptName("LEVEL ONE DEATH RUN");
}

//runs the script
void GameTesting::RunScript()
{
    //the aScriptName has not been set
    if(aScriptName.isEmpty())
    {
        return;
    }
    //create a script
    else
    {
        QScriptEngine engine;
        //level one death run is selected
        if (aScriptName == "LEVEL ONE DEATH RUN")
        {
            QFile scriptFile("leveloned.txt");
            if(scriptFile.open(QIODevice::ReadOnly))
            {
                qDebug() << "leveloned.txt unable to be read"<< endl;
            }
            QTextStream stream(&scriptFile);
            QString contents = stream.readAll();
            scriptFile.close();
            engine.evaluate(contents, "leveloned.txt");
            //qDebug() << "Code in RunScript() was executed" << endl;

        }
        //Level One Win run is selected
        else if (aScriptName == "LEVEL ONE WIN RUN")
        {

        }
    }

}
//Creates the demo menu button and connects it to the menu widget
void GameTesting::CreateDemoMenu(QMainWindow* mw){

    //Create the demo mode button
    aDemoButton = new QPushButton("Demo Mode", mw);
    //set size and location of the button
    aDemoButton->setGeometry(QRect(QPoint(10,530),QSize(100,50)));

    //connect button signal to appropriate slot
    aDemoMenu = new QWidget(mw);
    aDemoMenu->setWindowFlags(Qt::Window);
    aDemoMenu->setMinimumHeight(300);
    aDemoMenu->setMinimumWidth(300);
    QObject::connect(aDemoButton, SIGNAL(clicked()), aDemoMenu, SLOT(show()));
    //creates level one death check box
    aLevelOneDCheck = new QCheckBox("Level 1 (die)", aDemoMenu);
    aLevelOneDCheck->setChecked(false);
    aLevelOneDCheck->setGeometry(QRect(QPoint(10,10), QSize(100,35)));
    //creates level one win check box
    aLevelOneWCheck = new QCheckBox("Level 1 (win)", aDemoMenu);
    aLevelOneWCheck->setChecked(false);
    aLevelOneWCheck->setGeometry(QRect(QPoint(10, 120), QSize(100,35)));
    //creates run Demo button
    aRunDemoButton = new QPushButton("Run Demo", aDemoMenu);
    aRunDemoButton->setGeometry(QRect(QPoint(130, 200), QSize(100, 35)));
    //connects run script button to OnRunDemoButtonClicked()
    QObject::connect(aRunDemoButton, SIGNAL(clicked()), this, SLOT(OnRunDemoButtonClicked()));
    //qDebug() << "Something in create_demo_menu()" << endl;
    //this->RunScript();

}
//sets the attribut aMainWindow
void GameTesting::SetAMainWindow(MainWindow *mw){
    aMainWindow = mw;
}

//The function that is called when the run demo button is clicked
void GameTesting::OnRunDemoButtonClicked()
{
   // qDebug() << "Something in OnRunDemoButtonClicked()" << endl;
    //checks that there is a new game, if there is not a new game it prints an error
    if(!aMainWindow->Engine->isStarted())
    {
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setText("Please start a new game before entering Demo Mode !");
            Msgbox->exec();
            delete Msgbox;

    }
    //if there is a new game
    else
    {
        //if only aLevelOneDCheck is checked
        if (aLevelOneDCheck->isChecked() && !aLevelOneWCheck->isChecked())
        {
              SetAScriptName("LEVEL ONE DEATH RUN");
              this->RunScript();
        }
        //if only aLevelOneWCheck is checked
         else if (aLevelOneWCheck->isChecked() && !aLevelOneDCheck->isChecked())
        {
              SetAScriptName("LEVEL ONE WIN RUN");
              this->RunScript();
        }
        //if multiple check boxes are checked
        else
        {
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setText("Please select only one Demo Mode !");
            Msgbox->exec();
            delete Msgbox;
        }
    }

}

//sets the attribute aScriptName
void GameTesting::SetAScriptName(QString input)
{
    //qDebug()<< "In SetAScriptName(input)" <<endl;
    //if it is a valid entry
    if (input == "LEVEL ONE WIN RUN" || input == "LEVEL ONE DEATH RUN")
    {
        aScriptName = input;
    }
    //if it is not a valid entry
    else
    {
        qDebug() << "SetAScriptName did not receive a valid string as input" << endl;
    }
}
