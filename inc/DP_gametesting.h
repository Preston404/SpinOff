#ifndef GAMETESTING_H
#define GAMETESTING_H

#include "inc/AA_mainwindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QString>
#include <QScriptEngine>

class GameTesting : public QWidget
{
    Q_OBJECT
public:
    //sets the attribute aMainWindow
    void SetAMainWindow(MainWindow * mw);
    //Gets the singleton instance of GameTesting
    static GameTesting * GetInstance();

signals:

public slots:
    //Plays the win demo mode
    void OnWinScriptSelected();
    //plays the loose demo mode
    void OnLooseScriptSelected();
private:
    //instance of mainwindow that is used to create pop up widgets
    MainWindow * aMainWindow;
    //unique singleton instance of GameTesting
    static GameTesting * aUniqueInstance;
    //GameTesting constructor
    explicit GameTesting(QWidget *parent = nullptr);
};


#endif // DP_GAMETESTING_H
