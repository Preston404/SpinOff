#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    //Unique ID for each player, created by using the UNIX time stamp, the gam engine will grant each player a unique ID when created.
    int ID;
    //Name of the player used to login
    QString Name;
    //Password of the player
    QString Password;
    //Last Score by this player
    int Score;
    //Current reached level in this game
    int CurrentLevel;

signals:

public slots:
};

#endif // PLAYER_H
