#include "inc/DP_gametesting.h"
#include "inc/AA_mainwindow.h"
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>
#include <QWidget>
#include <QScriptClass>

gametesting::gametesting(QWidget *parent) : QWidget(parent)
{
    set_m_script_name("LEVEL ONE DEATH RUN");
}


void gametesting::run_script()
{
    if(m_script_name.isEmpty())
    {
        return;
    }
    else
    {
        QScriptEngine engine;
        if(m_script_name == "LEVEL ONE DEATH RUN")
        {


        }
        else if(m_script_name == "LEVEL ONE WIN RUN")
        {

        }
    }

}
void gametesting::create_demo_menu(QMainWindow* mw){

    //Create the demo mode button
    m_demo_button = new QPushButton("Demo Mode", mw);
    //set size and location of the button
    m_demo_button->setGeometry(QRect(QPoint(10,520),QSize(100,50)));

    //connect button signal to appropriate slot
    m_demo_menu = new QWidget(mw);
    m_demo_menu->setWindowFlags(Qt::Window);
    m_demo_menu->setMinimumHeight(300);
    m_demo_menu->setMinimumWidth(300);
    QObject::connect(m_demo_button, SIGNAL(clicked()), m_demo_menu, SLOT(show()));
    m_level_one_d_check = new QCheckBox("Level 1 (die)", m_demo_menu);
    m_level_one_d_check->setChecked(false);
    m_level_one_d_check->setGeometry(QRect(QPoint(10,10), QSize(100,35)));
    
    m_level_one_w_check = new QCheckBox("Level 1 (win)", m_demo_menu);
    m_level_one_w_check->setChecked(false);
    m_level_one_w_check->setGeometry(QRect(QPoint(10, 120), QSize(100,35)));

    m_run_script_button = new QPushButton("Run Script", m_demo_menu);
    m_run_script_button->setGeometry(QRect(QPoint(130, 200), QSize(100, 35)));

    QObject::connect(m_run_script_button, SIGNAL(clicked()), this, SLOT(on_run_demo_button_clicked()));
    qDebug() << "something";


}

void gametesting::set_m_main_window(MainWindow *mw){
    m_main_window = mw;
}

//expeditions unknown      josh gates   dshcs 278
void gametesting::on_run_demo_button_clicked()
{
    if(!m_main_window->Engine->isStarted())
    {
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setText("Please start a new game before entering Demo Mode !");
            Msgbox->exec();
            delete Msgbox;

    }

    else
    {
        if(m_level_one_d_check->isChecked() && !m_level_one_w_check->isChecked())
        {
              set_m_script_name("LEVEL ONE DEATH RUN");
              this->run_script();
        }
         else if(m_level_one_w_check->isChecked() && !m_level_one_d_check->isChecked())
        {
              set_m_script_name("LEVEL ONE WIN RUN");
              this->run_script();
        }
        else
        {
            QMessageBox *Msgbox = new QMessageBox(this);
            Msgbox->setIcon(QMessageBox::Critical);
            Msgbox->setText("Please select only one Demo Mode !");
            Msgbox->exec();
            delete Msgbox;
        }
    }

}

void gametesting::set_m_script_name(QString input)
{
    if(input == "LEVEL ONE WIN RUN" || input == "LEVEL ONE DEATH RUN")
    {    
	m_script_name = input;
    }
}
