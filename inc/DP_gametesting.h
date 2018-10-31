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
    void CreateDemoMenu(QMainWindow * mw);
    explicit GameTesting(QWidget *parent = nullptr);
    void SetAScriptName(QString input);
    void RunScript();
    void SetAMainWindow(MainWindow * mw);

signals:

public slots:
    void OnRunDemoButtonClicked();

private:
    QPushButton * aDemoButton;
    QCheckBox * aLevelOneDCheck;
    QCheckBox * aLevelOneWCheck;
    QPushButton * aRunDemoButton;
    QWidget * aDemoMenu;
    QString aScriptName;
    MainWindow * aMainWindow;

};


#endif // DP_GAMETESTING_H
