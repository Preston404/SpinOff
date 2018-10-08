#include "inc/Baoying/dialogloadplayer.h"
#include "ui_dialogloadplayer.h"
#include <QMessageBox>


DialogLoadPlayer::DialogLoadPlayer(QWidget *parent) :  QDialog(parent),  ui(new Ui::DialogLoadPlayer){
    ui->setupUi(this);
}

DialogLoadPlayer::~DialogLoadPlayer(){
    delete ui;
}


//The user clicked OK
void DialogLoadPlayer::on_buttonBox_accepted(){
    //Check the name input !
    if(ui->lineEditPlayerName->text().trimmed().length() == 0)   {
        //The name is not valid !
        QMessageBox *Msgbox = new QMessageBox(this);
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setText("You must enetr a valid user name !");
        Msgbox->exec();
        delete Msgbox;
        return;
    }


    //Check the password input if it's empty ?!
    if(ui->lineEditPWD->text().trimmed().length() == 0)    {
        //The name is not valid !
        QMessageBox *Msgbox = new QMessageBox(this);
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setText("You must enetr a valid password !");
        Msgbox->exec();
        delete Msgbox;
        return;
    }



//    //Check the ID input if it's a valid INT
//    //You can use QString::toInt() method. Which take an optional boolean pointer as argument, giving the result of the conversion.
//    bool ok;
//    int parsedID = ui->lineEditID->text().toInt(&ok, 10);
//    if(!ok)
//    {
//        //The name is not valid !
//        QMessageBox *Msgbox = new QMessageBox(this);
//        Msgbox->setIcon(QMessageBox::Critical);
//        Msgbox->setText("You must enetr a valid user ID !");
//        Msgbox->exec();
//        delete Msgbox;

//        //Keep the dialog open
//        return;
//    }

    this->PlayerPassword= ui->lineEditPWD->text().trimmed();
    this->PlayerName = ui->lineEditPlayerName->text().trimmed();
    //After passing all these checks we can close the dialog
    this->accept();
}

//Hides the modal dialog and sets the result code to Rejected.
void DialogLoadPlayer::on_buttonBox_rejected(){
    this->reject();
}
