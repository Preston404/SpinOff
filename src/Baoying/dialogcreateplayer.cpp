#include "inc/BL_dialogcreateplayer.h"
#include "ui_dialogcreateplayer.h"
#include <QPixmap>

DialogCreatePlayer::DialogCreatePlayer(QWidget *parent) : QDialog(parent),  ui(new Ui::DialogCreatePlayer){
    ui->setupUi(this);
    QPixmap pix(":images/Spinoff.PNG");
    int w = ui->pic->width();
    int h = ui->pic->height();
    ui->pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

DialogCreatePlayer::~DialogCreatePlayer(){
    delete ui;
}



//The user clicked OK
void DialogCreatePlayer::on_buttonBox_accepted(){
    //Check the name input !
    if(ui->lineEditPlayerName->text().trimmed().length() == 0)    {
        //The name is not valid !
        QMessageBox *Msgbox = new QMessageBox(this);
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setText("You must enetr a valid user name !");
        Msgbox->exec();
        delete Msgbox;
        return;
    }

    //Check the password input if it's empty ?!
    if(ui->lineEditPWD->text().trimmed().length() < 4){
        //The name is not valid !
        QMessageBox *Msgbox = new QMessageBox(this);
        Msgbox->setIcon(QMessageBox::Critical);
        Msgbox->setText("The password must be at least 4 letters !");
        Msgbox->exec();
        delete Msgbox;
        return;
    }
    this->PlayerPassword= ui->lineEditPWD->text().trimmed();
    this->PlayerName = ui->lineEditPlayerName->text().trimmed();
    //After passing all these checks we can close the dialog
    this->accept();
}


//Hides the modal dialog and sets the result code to Rejected.
void DialogCreatePlayer::on_buttonBox_rejected(){
    this->reject();
}
