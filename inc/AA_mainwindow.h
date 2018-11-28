#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsView>
#include <inc/BL_dialogloadplayer.h>
#include <inc/BL_dialogcreateplayer.h>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>
#include <QPainter>
#include <QLayout>
#include <QTimer>
#include "inc/AA_gameengine.h"

/*
 This macro makes the game compile in key testing mode
 Key testing mode will give 15 seconds to load a player and start a
 game and then it will simulate spamming all keyboard inputs (except "left button") at 1000 times per second
 The player is invincible in key test mode and this test also serves as a demo mode
*/
//#define TEST_KEYS // <- uncomment this macro to run key test mode

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GameEngine* Engine;
    GameModel* Model;

    //The player currently using the game
    Player* ActivePlayer = nullptr;
    QTimer* timer;

public slots:
    void LooseRun();
protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_action_New_Player_triggered();
    void on_action_Load_Player_triggered();
    void on_actionNew_Game_triggered();
    void StartNewGame(Player* player);
    void UpdateFrame(GameEngine* eng);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void testKeys();

    void on_actionHelp_triggered();

    void on_actionManual_triggered();


    void on_actionCoin_Overload_triggered();
    void on_actionWin_Script_triggered();

    void on_actionLoose_Script_triggered();

    void on_actionLevel_2_triggered();

    void on_actionBrick_Overload_triggered();
    void on_actionEnemy_Overload_triggered();

    void on_actionLevel_1_triggered();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
