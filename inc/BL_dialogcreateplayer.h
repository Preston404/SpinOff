#ifndef DIALOGCREATEPLAYER_H
#define DIALOGCREATEPLAYER_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class DialogCreatePlayer;
}

class DialogCreatePlayer : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreatePlayer(QWidget *parent = 0);
    ~DialogCreatePlayer();


    //--------------------------------------------------------------
    //Fields
    //--------------------------------------------------------------

    QString PlayerPassword;
    QString PlayerName;


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DialogCreatePlayer *ui;
};

#endif // DIALOGCREATEPLAYER_H
