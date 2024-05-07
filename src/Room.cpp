//#include <QGuiApplication>
#include <iostream>
#include "src/Room.h"
//#include <QString>
//#include <QMap>
//#include <QPixmap>



Room::Room(string name, string description) :
    Entity(name, description)
{
    type = ROOM;
}

Room::~Room()
{
}

void Room::Look() {
    std::cout << name << endl;
    std::cout << description << endl;

    for(int i = 0; i < exits.size(); i++) {
        std::cout << i << ") " << exits.at(i)->getName() << endl;
    }
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

void Room::addExit(Exit* exit) {
    exits.push_back(exit);
}

const vector<Exit *> Room::getExits() {
    return exits;
}
