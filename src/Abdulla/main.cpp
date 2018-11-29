
#include "inc/AA_mainwindow.h"
#include <QApplication>
#include <QException>
#include <QtDebug>
#include <time.h>

class WidgetVP;

int main(int argc, char *argv[]){
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
