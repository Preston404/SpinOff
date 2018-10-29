#ifndef GAMETESTING_H
#define GAMETESTING_H

#include "inc/AA_mainwindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QString>
#include <QScriptEngine>

class gametesting : public QWidget
{
    Q_OBJECT
public:
    void create_demo_menu(QMainWindow * mw);
    explicit gametesting(QWidget *parent = nullptr);
    void set_m_script_name(QString input);
    void run_script();
    void set_m_main_window(MainWindow * mw);

signals:

public slots:
    void on_run_demo_button_clicked();

private:
    QPushButton * m_demo_button;
    QCheckBox * m_level_one_d_check;
    QCheckBox * m_level_one_w_check;
    QPushButton * m_run_script_button;
    QWidget * m_demo_menu;
    QString m_script_name;
    MainWindow * m_main_window;

};


#endif // DP_GAMETESTING_H
