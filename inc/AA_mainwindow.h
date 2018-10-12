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

#include "inc/AA_gameengine.h"

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

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_action_New_Player_triggered();
    void on_action_Load_Player_triggered();
    void on_actionNew_Game_triggered();
    void StartNewGame(Player* player);
    void UpdateFrame(GameEngine* eng);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
