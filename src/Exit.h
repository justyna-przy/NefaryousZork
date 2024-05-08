#pragma once

#include <QObject>
#include <QPointer>
#include "Entity.h"
#include "Room.h"

class Room;

class Exit : public QObject , public Entity{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(Room* destination READ getDestination CONSTANT)

public:
    Exit(string name, string description, Room* origin, Room* destination, bool locked);
    ~Exit();
    QString getName() const { return QString::fromStdString(name);}
    QString getDescription() const { return QString::fromStdString(description);}
    Room* getDestination() const { return destination; }
    Room* getOrigin() const { return origin; }
    bool locked;

private:
    QPointer<Room> origin;
    QPointer<Room> destination;
};