
#include <iostream>
#include <utility>
#include "src/Room.h"
#include <qdebug.h>
//#include <QString>
//#include <QMap>
//#include <QPixmap>



Room::Room(string name, string description, QObject *parent = nullptr) : QObject(parent),
    // Moving it to the entity constructor instead of copying it!
    Entity(std::move(name), std::move(description))
{
    type = ROOM;
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

QVector<QObject*> Room::getExits() const{
    qDebug() << "Accessing exits, count:" << exits.count();
    QVector<QObject*> list;
    for (const QPointer<Exit>& exit : exits) {
        if (exit) {
            list.append(exit);
        }
    }
    qDebug() << "returning list";
    return list;
}







//
//void Room::addState(const QString& state, const QString& imagePath) {
//    roomImages[state] = QPixmap(imagePath);
//    currentState = state;
//}

//
//void Room::setState(const QString& state) {
//    if (roomImages.contains(state)) {
//        currentState = state;
//    }
//}

//QPixmap Room::getCurrentImage() {
//    return roomImages.value(currentState, QPixmap()); // returns and empty QPixmap if not found
//}
