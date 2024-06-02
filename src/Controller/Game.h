#pragma once

#include <QObject>
#include <QMap>
#include "src/Model/Room.h"



class Game : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString gameLog READ getGameLog NOTIFY gameLogChanged)
    Q_PROPERTY(Room* currentRoom READ getCurrentRoom NOTIFY currentRoomChanged)
//    Q_PROPERTY(QVector<QObject*> exits READ getExits NOTIFY exitsChanged)

public:
    // Use explicit to avoid unintended conversions from QObject to Game object
    explicit Game(QObject *parent = nullptr);
    void initRooms();
    QString getGameLog() const { return gameLog; }
    Room* getCurrentRoom() const { return currentRoom; }
    void addRoom(const QString &name, Room *room);
    void setCurrentRoom(Room *room);
    void addToGameLog(const QString &roomName);
//    QVector<QObject*> getExits();


private:
    QMap<QString, Room*> rooms;
    Room *currentRoom;
    QString gameLog;
//    QVector<QPointer<Exit>> exits;

signals:
    void gameLogChanged();
    void currentRoomChanged();

public slots:
    void moveToRoom(Room *room);
};
