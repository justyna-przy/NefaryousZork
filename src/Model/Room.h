#pragma once
#include "Entity.h"
#include "Exit.h"
#include "Item.h"
#include <vector>
#include <QObject>

class Interactable;

using namespace std;
class Exit;
class Item;
class Interactable;

// QObject must be first base class
// Determines the order in which constructors and destructors are called
class Room : public QObject, public Entity {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString description READ getDescription CONSTANT)
    Q_PROPERTY(QVector<QObject*> exits READ getExits NOTIFY exitsChanged)
    Q_PROPERTY(QVector<QObject*> roomItems READ getRoomItems NOTIFY roomItemsChanged)
    Q_PROPERTY(Interactable* interactable READ getInteractable CONSTANT)
    Q_PROPERTY(QString roomImage READ getImage CONSTANT)


public:
    Room(string name, string description, string imageName, QObject *parent);
    ~Room() override;
    QString getName() const { return QString::fromStdString(name);}
    QString getDescription() const { return QString::fromStdString(description);}
    void addExit(Exit* exit);
    void addItem(Item* item);
    void setInteractable(Interactable* interactable);
    QVector<QObject*> getExits() const; // const prevents modification to the original vector
    QVector<QObject*> getRoomItems();
    Interactable* getInteractable();
    QString getImage() const { return roomImage; }

    friend class Game;
private:
    // Automatically nullifies pointers if the pointed-to Exit objects are deleted elsewhere
    QVector<QPointer<Exit>> exits;
    QVector<QPointer<Item>> roomItems;
    Interactable* interactable;
    QString roomImage;

signals:
    void exitsChanged();
    void roomItemsChanged();
};