#ifndef DIALOGLOADPLAYER_H
#define DIALOGLOADPLAYER_H

#include <QDialog>

namespace Ui {
class DialogLoadPlayer;
}

class DialogLoadPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLoadPlayer(QWidget *parent = 0);
    ~DialogLoadPlayer();



    //--------------------------------------------------------------
    //Fields
    //--------------------------------------------------------------

    QString PlayerPassword;
    QString PlayerName;


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DialogLoadPlayer *ui;
};

#endif // DIALOGLOADPLAYER_H
