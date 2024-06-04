#pragma once

#include <QObject>
#include <QMap>
#include "../Model/Room.h"
#include "../Model/Inventory.h"
#include "../Model/Player.h"
#include "../Model/Weapon.h"
#include "../Model/Potion.h"


class Game : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString gameLog READ getGameLog NOTIFY gameLogChanged)
    Q_PROPERTY(Room* currentRoom READ getCurrentRoom NOTIFY currentRoomChanged)
    Q_PROPERTY(ItemInventory* inventory READ getInventory CONSTANT)
    Q_PROPERTY(Player* player READ getPlayer CONSTANT)
    Q_PROPERTY(QVector<Potion*> potions READ getPotions NOTIFY inventoryChanged)

public:
    // Use explicit to avoid unintended conversions from QObject to Game object
    explicit Game(QObject *parent = nullptr);
    void initRooms();
    QString getGameLog() const { return gameLog; }
    Room* getCurrentRoom() const { return currentRoom; }
    void addRoom(const QString &name, Room *room);
    void setCurrentRoom(Room *room);
    Q_INVOKABLE void addToGameLog(const QString &message);
    ItemInventory* getInventory() { return &inventory; }
    Player* getPlayer() const { return &Player::instance();}
    void cloningSpell(Key &key);
    Weapon* playerGetWeapon();
    Key* playerGetKey();
    QVector<Potion*> getPotions();


private:
    QMap<QString, Room*> rooms;
    Room *currentRoom;
    QString gameLog;
    ItemInventory inventory;
    QVector<Potion*> potions;

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