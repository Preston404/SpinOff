#ifndef CREATELEVEL_H
#define CREATELEVEL_H

#include"inc/AA_mainwindow.h"

class CreateLevel{
    public:
        //constructor
        CreateLevel();
        //resets an object
        void Reset();
        //generates a new level
        void GenerateLevel();
        //sets aMainWindow
        void SetAMainWindow(MainWindow *mw);
private:
        bool aComplete;
        MainWindow * aMainWindow;
};


#endif //createlevel.h
