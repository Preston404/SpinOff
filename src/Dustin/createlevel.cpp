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
    QString errmsg;
    QFileDevice::FileError err = QFileDevice::NoError;
    //find the current directory

    QString directory = QDir::currentPath();
    QDir::setCurrent("..");
    QString filename = QDir::currentPath();
    QDir::setCurrent(directory);
    filename.append("/Randomly_Generated_File.txt");
    qDebug() << filename << endl;
    QFile file(filename);

        //if the file is successfully opened for write only
        if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
            qDebug() << "opened successfully" << endl;
            QTextStream stream(&file);
            qDebug() <<"writing to file" << endl;
            //highest level of the level

            stream << "f ";
            for(i = 0; i < 300; i++){
                stream << "0";
            }
            stream << endl;
            //next level down (some chance of an enemy)
            stream << "e ";
            for(i = 0; i < 300; i++){
                if(i < 5){
                    //add a coin
                    stream << "9";
                }
                else
                    stream << "0";
            }
            stream << endl;
            //next level, row d
            stream << "d ";
            for(i = 0; i < 275; i++){
                j = rand() % 30;
                //creates a block with grass
                if(j >10 && j < 14){
                    stream << "7";
                }
                //creates a coin
                else if(j > 14 && j< 30){
                    stream << "9";
                }
                else{
                    stream << "0";
                }
            }
            for(i = 0; i < 25; i++){
                stream << "0";
            }
            stream << endl;
            file.flush();
            //next level, row c
            stream << "c ";
            for(i = 0; i < 275; i++){
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
                //creates a coin
                else if(j > 15 && j< 30){
                    stream << "9";
                }
                else{
                    stream << "0";
                }
            }            
            for(i = 0; i < 25; i++){
                stream << "0";
            }
            stream << endl;
            //next level, row b
            stream << "b ";
            for(i = 0; i < 300; i++){
                stream << "7";
            }
            stream << endl;
            //lowest level of the level
            stream << "a ";
            for(i = 0; i < 300; i++){
                stream << "1";
            }
            stream << endl;
            file.close();
            //print success message
            QMessageBox *Msgbox = new QMessageBox(aMainWindow);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setGeometry(300, 400, 200, 50);
            Msgbox->setText("Success ! New level generated ! To play select Game->Level Selector->Randomly Generated !");
            Msgbox->exec();
            delete Msgbox;
            aComplete = true;
        }
        //print file error message
        else{
            errmsg = file.errorString();
            err= file.error();
            qDebug() << errmsg << endl;
            qDebug() << err << endl;
            //print success message
            QMessageBox *Msgbox = new QMessageBox(aMainWindow);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setGeometry(300, 400, 200, 50);
            Msgbox->setText("Error ! The file could not be opened !");
            Msgbox->exec();
            delete Msgbox;
            aComplete = true;
        }

        return;
}
