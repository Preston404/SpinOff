#include "mainwindow.h"
#include <QApplication>
#include <QException>
#include <QtDebug>

class WidgetVP;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
