#pragma once

#include <QObject>
#include <QMap>
#include "../Model/Room.h"
#include "../Model/Inventory.h"
#include "../Model/Player.h"
#include "../Model/Weapon.h"



class Game : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString gameLog READ getGameLog NOTIFY gameLogChanged)
    Q_PROPERTY(Room* currentRoom READ getCurrentRoom NOTIFY currentRoomChanged)
    Q_PROPERTY(ItemInventory* inventory READ getInventory CONSTANT)
    Q_PROPERTY(Player* player READ getPlayer CONSTANT)



public:
    // Use explicit to avoid unintended conversions from QObject to Game object
    explicit Game(QObject *parent = nullptr);
    void initRooms();
    QString getGameLog() const { return gameLog; }
    Room* getCurrentRoom() const { return currentRoom; }
    void addRoom(const QString &name, Room *room);
    void setCurrentRoom(Room *room);
    void addToGameLog(const QString &message);
    ItemInventory* getInventory() { return &inventory; }
    Player* getPlayer() const { return &Player::instance();}
    void cloningSpell(Key &key);
    Weapon* playerGetWeapon();

private:
    QMap<QString, Room*> rooms;
    Room *currentRoom;
    QString gameLog;
    ItemInventory inventory;

signals:
    void gameLogChanged();
    void roomItemsChanged();
    void currentRoomChanged();
    void inventoryChanged();
    void resetUIState();

public slots:
    void moveToRoom(Room *room);
    void pickUpItem(const QString &itemName);
    void checkRoomForItems();
};

extern Game game;