
#include <qdebug.h>
#include <memory>
#include <thread>
#include "Game.h"
#include "../Model/Weapon.h"

Game::Game(QObject *parent) : QObject(parent), currentRoom(nullptr)
{
    gameLog = "Welcome to Nefaryous \n";
    initRooms();
}


// Add a room to the game
void Game::addRoom(const QString &name, Room *room) {
    rooms.insert(name, room);
}

// Set the current room
void Game::setCurrentRoom(Room *room) {
    if (currentRoom != room) {
        currentRoom = room;
        emit currentRoomChanged();  // Notify that the current room has changed
        addToGameLog(room->getDescription());  // Log the room change
    }
}

// Move to a specified room by name
void Game::moveToRoom(Room *room) {
    qDebug() << "Moving to room:" << room->getDescription();
    setCurrentRoom(room);
    emit currentRoomChanged();
    emit resetUIState();
}

// Add a message to the game log
void Game::addToGameLog(const QString &message) {
    gameLog += message + "\n";
    emit gameLogChanged();  // Notify that the game log has changed
}


void Game::pickUpItem(const QString &itemName) {
    auto &items = currentRoom->roomItems;

    auto it = std::find_if(items.begin(), items.end(), [&](const QPointer<Item> &item) {
        return item && item->getName() == itemName;
    });

    if (it != items.end()) {
        QPointer<Item> item = *it;
        inventory.addItem(item);
        items.erase(it);
        emit currentRoom->roomItemsChanged();
        addToGameLog("Picked up: " + itemName);
        emit inventoryChanged();
    }
}


void Game::checkRoomForItems() {
    if (currentRoom->roomItems.isEmpty()) {
        addToGameLog("There are no items in this room.");
    } else {
        // auto tells the compiler to deduce the type of the variable from its initializer
        for (const auto &roomItem : currentRoom->roomItems) {
            addToGameLog(roomItem->getDescription());
        }
    }
    emit gameLogChanged();
}


void Game::cloningSpell(Key &key) {
    // First Check if the player's inventory is full
    if(inventory.isFull()) {
        addToGameLog("You can't clone an item because your inventory is full!");
        emit gameLogChanged();
        return;
    }
    // Check if the player has a weapon to perform a blood ritual
    Weapon* weapon = playerGetWeapon();
    if (!weapon) {
        addToGameLog("You need a weapon to perform this ritual! Go find one.");
        emit gameLogChanged();
        return;
    }
    // Use the weapon, and reduce hp
    weapon->use();
    emit gameLogChanged();

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Once you make the sacrifice, the spell is activated.
    std::shared_ptr<Item> clone = std::make_shared<Key>(key);
    inventory.addItem(clone);
}

Weapon* Game::playerGetWeapon(){
    for (int i = 0; i < inventory.count(); ++i) {
        Item* item = dynamic_cast<Item*>(inventory.getItem(i));
        if (item) {
            Weapon* weapon = dynamic_cast<Weapon*>(item);
            return weapon;
        }
    }

}



void Game::initRooms() {

    Room* bridgeEntrance = new Room("Bridge", "You stand in front of a crumbling gothic bridge. Dazed, you begin to inspect your surroundings. The sky is outer-wordly, with a pink hue and dazzling yellow galaxies. You look back and see a luscious forrest. Where will you go next? ", "entancetobridge.png", this);
    Room* forestEntrance = new Room("Forest Entrance", "You enter the forest and follow its path. Once you emerge into a clearing, three winding paths appear in front of you. One leads to a dark forest that is guarded by stone gates. The other two wind off into opposite directions. Which path will you take?", "forrestenter.png", this);
    Room* frontOfCastle = new Room("Castle", "Once you crossed the bridge, you look up in awe of the abandoned castle towering over you. To your left, a paved path winds around the castle. The ornate doors of the castle look heavy. Where will you go?", "castlefront.jpeg", this);
    Room* churchEntrance = new Room("Church Entrance", "You follow the path and stumble across a cosy-looking church. Will you enter the church?", "churchentrance.png", this);
    Room* alterRoom = new Room("Alter Room", "You push open the church doors to reveal an unsettling scene - A domed room with a sacrificial altar surrounded by pews. Eerie moonlight shines onto the alter through a crack in the roof. A dim light shines from a doorway on the right of the room...", "alterroom.png", this);
    Room* catacombEntrance = new Room("Catacombs", "You follow the light out of the alter room. You find long and twisted catacombs ahead. As you enter, you notice the rancid smell. The walls are lined with skulls which are illuminated by the green flames from the torches.", "catacombentrance.jpeg", this);
    Room* catacombHallway = new Room("Catacombs", "As you turn the corner, you see just how far these catacombs stretch out. Your stomach sinks and the smell makes you feel sick. Do you turn back or keep going?", "catacombhallway.jpeg", this);
    Room* catacombExit = new Room("End of the Catacombs", "You push through the catacombs. With each step, the hairs on your neck stand taller. After some time, you reach an ominous door. Open the door?", "undergroundentrance.jpeg", this);
    Room* castleEntrance = new Room("Castle Entrance Room", "Upon opening the door, you find yourself in a grand room. This room looks like its been abandoned for centuries. Cracks have begun to form in the magnificent windows. There appears to be a hallway up the stairs.", "castleentrance.png", this);
//    Room* castleHallway = new Room("Castle Hallway", "")

    Exit* bridgeToCastle = new Exit("Crumbling Bridge", "A crumbling stone bridge", bridgeEntrance, frontOfCastle, false);
    Exit* bridgeToForrest = new Exit("Forest path", "A tall grim forest with a dark path", bridgeEntrance, forestEntrance, false);
    Exit* forestToBridge = new Exit("Path back to the Bridge", "The path winds back to the crumbling gothic bridge", forestEntrance, bridgeEntrance, false);
    Exit* castleToBridge = new Exit("Path back to the Bridge", "A stone path leading back to the bridge", frontOfCastle, bridgeEntrance, false);
    Exit* castleToChurch = new Exit("Paved path", "Path that winds around the castle", frontOfCastle, churchEntrance,false);
    Exit* churchToCastle = new Exit("Path back to the Castle", "Path that winds around the castle", churchEntrance, frontOfCastle,false);
    Exit* churchToAlter = new Exit("Church doors", "Tall wooden doors in front of the church", churchEntrance, alterRoom,false);
    Exit* alterToChurch = new Exit("Church doors", "Tall wooden doors in front of the church", alterRoom, churchEntrance,false);
    Exit* alterToCatacombs = new Exit("Dimly lit doorway", "A doorway leading to dark and twisted catacombs.", alterRoom, catacombEntrance, false);
    Exit* catacombsToAlter = new Exit("Way back to the Alter Room", "The path leading back to the unsettling alter room.", catacombEntrance, alterRoom, false);
    Exit* catacombEntranceToHallway = new Exit("Deeper into the Catacombs", "A narrow passage that leads deeper into the darkness of the catacombs.", catacombEntrance, catacombHallway, false);
    Exit* catacombHallwayToEntrance = new Exit("Go Back!", "The path leading back to the entrance of the catacombs.", catacombHallway, catacombEntrance, false);
    Exit* hallwayToCatacombExit = new Exit("Ominous Door", "The ominous door at the end of the catacombs.", catacombHallway, catacombExit, false);
    Exit* catacombExitToHallway = new Exit("Back to the Catacombs", "The path leading back to the catacombs.", catacombExit, catacombHallway, false);



    catacombHallway->addExit(hallwayToCatacombExit);
    catacombExit->addExit(catacombExitToHallway);


    bridgeEntrance->addExit(bridgeToForrest);
    bridgeEntrance->addExit(bridgeToCastle);
    forestEntrance->addExit(forestToBridge);
    frontOfCastle->addExit(castleToBridge);
    frontOfCastle->addExit(castleToChurch);
    churchEntrance->addExit(churchToCastle);
    churchEntrance->addExit(churchToAlter);
    alterRoom->addExit(alterToChurch);
    alterRoom->addExit(alterToCatacombs);
    catacombEntrance->addExit(catacombsToAlter);
    catacombEntrance->addExit(catacombEntranceToHallway);
    catacombHallway->addExit(catacombHallwayToEntrance);



    Weapon* dagger = new Weapon("Mysterious Dagger", "A Mysterious Dagger lies on the ground in front of you", 3, "dagger.png");
    Key* key = new Key("Rustic Key", "An antique looking key", "key.png");

    inventory.addItem(dagger);
    inventory.addItem(key);

//    bridgeEntrance->addItem(dagger);
//    forestEntrance->addItem(key);

    setCurrentRoom(bridgeEntrance);

    emit inventoryChanged();

    cloningSpell(*key);
}

