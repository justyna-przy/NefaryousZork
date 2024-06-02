#include "src/Controller/Game.h"
#include <qdebug.h>

// Constructor
Game::Game(QObject *parent) : QObject(parent), currentRoom(nullptr) {
    gameLog = "Welcome to Nefaryous \n";
    initRooms();
}


void Game::initRooms() {
    // Create rooms
    Room* lobby = new Room("Lobby", "The main entrance of the game", this);
    Room* hallway = new Room("Hallway", "A long, narrow passage", this);
    Room* dungeon = new Room("Dungeon", "\n"
                                        "A formidable, heavy door stands as the gateway to the hallway. Crafted from thick, dark oak wood, its surface is adorned with intricate carvings that hint at the building's rich history. The brass handle, worn by the touch of countless hands, reflects a dull gleam under the flickering light from overhead.", this);

    // Create exits and link rooms
    Exit* lobbyToHallway = new Exit("Door to Hallway", "A heavy door leading to the hallway", lobby, hallway, false);
    Exit* hallwayToDungeon = new Exit("Stairs to Dungeon", "A narrow stairway down to the dungeon", hallway, dungeon, true);
    Exit* dungeonToHallway = new Exit("Stairs to Hallway", "Stairs leading up to the hallway", dungeon, hallway, false);

    lobby->addExit(lobbyToHallway);
    hallway->addExit(hallwayToDungeon);
    dungeon->addExit(dungeonToHallway);

    // Add rooms to the game's map
    addRoom("Lobby", lobby);
    addRoom("Hallway", hallway);
    addRoom("Dungeon", dungeon);
    // Optionally set an initial room
    setCurrentRoom(lobby);
}

// Add a room to the game
void Game::addRoom(const QString &name, Room *room) {
    // Insert the room into the map with the specified name
    rooms.insert(name, room);
}

// Set the current room
void Game::setCurrentRoom(Room *room) {
    if (currentRoom != room) {
        currentRoom = room;
        emit currentRoomChanged();  // Notify that the current room has changed
        addToGameLog("Entered room: " + room->getDescription());  // Log the room change
    }
}

// Move to a specified room by name
void Game::moveToRoom(Room *room) {
    qDebug() << "Moving to room:" << room->getDescription();
    setCurrentRoom(room);
}

// Add a message to the game log
void Game::addToGameLog(const QString &message) {
    gameLog += message + "\n";
    emit gameLogChanged();  // Notify that the game log has changed
}
//
//QVector<QObject*> Room::getExits() {
//    QVector<QObject*> list;
//    for (QPointer<Exit> exit : currentRoom.exits) {
//        list.append(static_cast<QObject*>(exit));  // Use static_cast for better type safety
//    }
//    return list;
//}
