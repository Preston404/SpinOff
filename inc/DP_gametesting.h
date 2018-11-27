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
    explicit GameTesting(QWidget *parent = nullptr);
    void SetAMainWindow(MainWindow * mw);

signals:

public slots:
    void OnWinScriptSelected();
    void OnLooseScriptSelected();
private:
    MainWindow * aMainWindow;

};


#endif // DP_GAMETESTING_H
