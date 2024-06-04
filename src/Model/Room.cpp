
#include <iostream>
#include <utility>
#include "Room.h"
#include <qdebug.h>



Room::Room(string name, string description, string imageName, QObject *parent = nullptr) : QObject(parent),
    // Moving it to the entity constructor instead of copying it!
    Entity(std::move(name), std::move(description)), interactable(nullptr)
{
    this->roomImage = QString::fromStdString("qrc:/qt/qml/content/images/" + imageName);
    this->type = ROOM;
}

Room::~Room() {
    for (Exit* exit : exits) {
        delete exit;
    }
    exits.clear();
}

void Room::addExit(Exit* exit) {
    exits.push_back(exit);
    emit exitsChanged();
}

void Room::addItem(Item *item) {
    roomItems.push_back(item);
    emit roomItemsChanged();
}

void Room::setInteractable(Interactable* interactable){
    this->interactable = interactable;
}

QVector<QObject*> Room::getExits() const {
    QVector<QObject*> list;
    for (const QPointer<Exit>& exit : exits) {
        if (exit) {
            list.append(exit);
        }
    }
    return list;
}

QVector<QObject*> Room::getRoomItems() {
    QVector<QObject*> list;
    for (const QPointer<Item>& item : roomItems) {
        if (item) {
            list.append(item);
        }
    }
    return list;
}

Interactable* Room::getInteractable() {
    return interactable;
}
