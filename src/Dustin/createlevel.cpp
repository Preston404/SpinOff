#include "inc/DP_createlevel.h"
#include "inc/AA_mainwindow.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

CreateLevel::CreateLevel(){
    aComplete = false;
}

//resets the completion variable
void CreateLevel::Reset(){
    aComplete = false;
}
void CreateLevel::SetAMainWindow(MainWindow * mw){
    aMainWindow = mw;
}
//generates a new level
void CreateLevel::GenerateLevel(){
    int i = 0, j;
    QString filename = ":Randomly_Generated_Level.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "Error, File does not exist" << endl;
        QMessageBox *Msgbox = new QMessageBox(aMainWindow);
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setGeometry(300, 400, 200, 50);
        Msgbox->setText("Error: Something went wrong !");
        Msgbox->exec();
        delete Msgbox;
        }
    else{
        //if the file is successfully opened for write only
        if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
            qDebug() << "opened successfully" << endl;
            QTextStream stream(&file);
            //highest level of the level
            stream << "f ";
            for(i = 0; i < 75; i++){
                stream << "0";
            }
            stream << endl;
            //next level down (some chance of an enemy)
            stream << "e ";
            for(i = 0; i < 75; i++){
                j = rand() % 30;
                //1/30 to create a critter
                if(j == 0){
                    stream << "4";
                }
                //1/30 to create a swordsman
                else if( j == 1){
                    stream << "6";
                }
                else{
                    stream << "0";
                }
            }
            stream << endl;
            //next level, row d
            stream << "d ";
            for(i = 0; i < 75; i++){
                j = rand() % 30;
                //2/30 to create a critter
                if(j < 2){
                    stream << "4";
                }
                //2/30 to create a swordsman
                else if(j == 2 || j == 3){
                    stream << "6";
                }
                else{
                    stream << "0";
                }
            }
            stream << endl;
            file.flush();
            //next level, row c
            stream << "c ";
            for(i = 0; i < 75; i++){
                j = rand() % 30;
                //4/30 to create a critter
                if(j < 4){
                    stream << "4";
                }
                //4/30 to create a swordsman
                else if(j > 4 && j < 9){
                    stream << "6";
                }
                //5/30 to create a block
                else if(j > 9 && j < 15){
                    stream << "7";
                }
                else{
                    stream << "0";
                }
            }
            stream << endl;
            //next level, row b
            stream << "b ";
            for(i = 0; i < 75; i++){
                j = rand() % 30;
                //4/30 to create a critter
                if(j < 4){
                    stream << "4";
                }
                //4/30 to create a swordsman
                else if(j > 4 && j < 9){
                    stream << "6";
                }
                //10/30 to create a block
                else if(j > 9 && j < 20){
                    stream << "1";
                }
                else{
                    stream << "0";
                }
            }
            stream << endl;
            //lowest level of the level
            stream << "a ";
            for(i = 0; i < 75; i++){
                stream << "1";
            }
            stream << endl;
            file.close();
        }
        //print success message
        QMessageBox *Msgbox = new QMessageBox(aMainWindow);
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setGeometry(300, 400, 200, 50);
        Msgbox->setText("Success ! New level generated ! To play select Game->Level Selector->Randomly Generated !");
        Msgbox->exec();
        delete Msgbox;
        aComplete = true;
    }
    return;
}
