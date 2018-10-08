#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

class Player : public QObject{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    //Unique ID , UNIX time stamp.
    int ID;
    //Player attributes
    QString Name;
    QString Password;
    int Score;
    //Current reached level in this game
    int CurrentLevel;

signals:

public slots:
};

#endif // PLAYER_H
