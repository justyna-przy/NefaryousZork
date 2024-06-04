#pragma once
#include "Entity.h"
#include "Exit.h"
#include "Item.h"
#include <vector>
#include <QObject>

using namespace std;
class Exit;
class Item;

// QObject must be first base class
// Determines the order in which constructors and destructors are called
class Room : public QObject, public Entity {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString description READ getDescription CONSTANT)
    Q_PROPERTY(QVector<QObject*> exits READ getExits NOTIFY exitsChanged)
    Q_PROPERTY(QVector<QObject*> roomItems READ getRoomItems NOTIFY roomItemsChanged)
    Q_PROPERTY(QString roomImage READ getImage CONSTANT)


public:
    Room(string name, string description, string imageName, QObject *parent);
    ~Room() override;
    QString getName() const { return QString::fromStdString(name);}
    QString getDescription() const { return QString::fromStdString(description);}
    void addExit(Exit* exit);
    void addItem(Item* item);
    QVector<QObject*> getExits() const; // const prevents modification to the original vector
    QVector<QObject*> getRoomItems(); // const prevents modification to the original vector
    QString getImage() const { return roomImage; }

    friend class Game;
private:
    // Automatically nullifies pointers if the pointed-to Exit objects are deleted elsewhere
    QVector<QPointer<Exit>> exits;
    QVector<QPointer<Item>> roomItems;
    QString roomImage;

signals:
    void exitsChanged();
    void roomItemsChanged();
};