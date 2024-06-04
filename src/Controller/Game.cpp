
#include <qdebug.h>
#include <memory>
#include <thread>
#include "Game.h"
#include "../Model/Interactable.h"

Game::Game(QObject *parent) : QObject(parent), currentRoom(nullptr)
{
    gameLog = "Welcome to Nefaryous \n";
    initRooms();
}



void Game::addRoom(const QString &name, Room *room) {
    rooms.insert(name, room);
}


void Game::setCurrentRoom(Room *room) {
    if (currentRoom != room) {
        currentRoom = room;
        emit currentRoomChanged();
        addToGameLog(room->getDescription());
    }
}


void Game::moveToRoom(Room *room) {
    qInfo() << room->name;
    qInfo() << currentRoom->name;

    Exit* roomExit;
    for(Exit* exit: currentRoom->exits) {
        if(exit->getDestination() == room) {
            roomExit = exit;
            qInfo() << roomExit->getName();
        }
    }

    if(roomExit->isLocked()) {
        QString message = "The " + roomExit->getName() + " is locked!";
        addToGameLog(message);

        Key* key = playerGetKey();
        if(!key) {
            addToGameLog("You check your inventory for a key, but find none");
            emit gameLogChanged();
            return;
        }
        else {
            addToGameLog("You check your inventory for a key, and find it. You use this key to unlock the room.");
            roomExit->unlock();
            key->use();
            inventory.removeUsedKeys();
        }
    }
    setCurrentRoom(room);
    emit gameLogChanged();
    emit currentRoomChanged();
    emit resetUIState();
}


void Game::addToGameLog(const QString &message) {
    gameLog += message + "\n";
    emit gameLogChanged();
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
        // auto tells the compiler to deduce the potionType of the variable from its initializer
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

    // Once you make the sacrifice, the spell is activated.
    std::shared_ptr<Item> clone = std::make_shared<Key>(key);
    inventory.addItem(clone);
    emit inventoryChanged();
}

Weapon* Game::playerGetWeapon() {
    for (int i = 0; i < inventory.count(); ++i) {
        QObject* obj = inventory.getItem(i);
        Item* item = qobject_cast<Item*>(obj);
        if (item && item->getType() == WEAPON) {
            qDebug() << "Weapon found: " << item->getName();
            return qobject_cast<Weapon*>(item);
        }
    }
    qDebug() << "No weapon found in inventory.";
    return nullptr;
}

Key* Game::playerGetKey() {
    for (int i = 0; i < inventory.count(); ++i) {
        QObject* obj = inventory.getItem(i);
        Item* item = qobject_cast<Item*>(obj);
        if (item && item->getType() == KEY) {
            return qobject_cast<Key*>(item);
        }
    }
    return nullptr;
}

QVector<Potion*> Game::getPotions() {
    QVector<Potion*> foundPotions;


    for (int i = 0; i < inventory.count(); ++i) {
        QObject* obj = inventory.getItem(i);
        Item* item = qobject_cast<Item*>(obj);
        if (item && item->getType() == POTION) {
            Potion* potion = dynamic_cast<Potion*>(item);
            if (potion) {
                foundPotions.append(potion);
            }
        }
    }
    return foundPotions;
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
    Room* castleHallway = new Room("Castle Hallway", "You begin walking through the hallway. The painting on the wall seem to be watching. There are three doors here, but one of them is boarded up. The other two are opposite to each other.", "hallway.jpeg", this);
    Room* bedroom = new Room("Master Bedroom", "You push the door open to find what was once an elegant bedroom. Light shines onto the dusty bed from the massive windows. All the furniture and sheets are torn apart.", "bedroom.jpeg", this);
    Room* library = new Room("The Library", "You find yourself in awe when you open the door. There stands the biggest library you have ever seen. Compared to the other rooms, this one is not quite as trashed, but the years of neglect remain apparent with the layer of dust", "library.jpeg", this);
    Room* stairs = new Room("The Stairwell", "When you enter the small room, you find a spiral staircase in the middle. You look down and it appears as if a glow is coming from the room below.", "stairwell.jpeg", this);
    Room* portalRoom = new Room("The Portal Room", "...... There is a portal. Its so bright and mesmerizing. You are drawn closer and closer, but should you step inside?", "portalroom.jpeg", this);
    Room* alter = new Room("The Alter", "The moonlight shines onto its the alter. Your mind feels calm, but you feel the sudden urge to hold a blade.. ", "alter.jpeg", this);

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
    Exit* catacombHallwayToExit = new Exit("Keep Going", "The catacomb tunnel stretches even further", castleHallway, catacombExit, false);
    Exit* catacombHallwayToEntrance = new Exit("Go Back!", "The path leading back to the entrance of the catacombs.", catacombHallway, catacombEntrance, false);
    Exit* catacombExitToHallway= new Exit("Ominous Door", "The ominous door at the end of the catacombs.", catacombExit, castleHallway, false);
    Exit* backToCatacombs = new Exit("Back to the Catacombs", "The path leading back to the catacombs.", catacombExit, catacombHallway, false);
    Exit* castleToEntrance = new Exit("Castle doors", "A pair of mighty carved doors", frontOfCastle, castleEntrance, true);
    Exit* entranceToHallway = new Exit("Hallway", "The hallway at the end of the entrance", castleEntrance, castleHallway, false);
    Exit* hallwayToBedroom = new Exit("Right Door", "A plain wooden door", castleHallway, bedroom, false);
    Exit* hallwayToLibrary = new Exit("Left Door", "A plain wooden door", castleHallway, library, false);
    Exit* libraryToStairs = new Exit("Small Door", "A small door at the back of the library", library, stairs, false);
    Exit* stairsToPortal = new Exit("Glowing room", "A faint glow coming from the room below", stairs, portalRoom, false);
    Exit* entranceToCastle = new Exit("Castle doors", "The path leading back to the Castle Entrance Room", castleHallway, castleEntrance, false);
    Exit* bedroomToHallway = new Exit("Back to the Hallway", "The door leading back to the Castle Hallway", bedroom, castleHallway, false);
    Exit* libraryToHallway = new Exit("Back to the Hallway", "The door leading back to the Castle Hallway", library, castleHallway, false);
    Exit* stairsToLibrary = new Exit("Back to the Library", "The door leading back to the Library", stairs, library, false);
    Exit* portalToStairs = new Exit("Back to the Stairwell", "The glowing exit leading back to the Stairwell", portalRoom, stairs, false);
    Exit* roomToAlter = new Exit("Go to Alter", "Its calling", alterRoom, alter, false);
    Exit* backFromAlter = new Exit("Step Back", "Its calling", alter, alterRoom, false);

    catacombHallway->addExit(catacombHallwayToExit);
    catacombExit->addExit(backToCatacombs);
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
    frontOfCastle->addExit(castleToEntrance);
    castleEntrance->addExit(entranceToHallway);
    castleHallway->addExit(hallwayToBedroom);
    castleHallway->addExit(hallwayToLibrary);
    bedroom->addExit(bedroomToHallway);
    library->addExit(libraryToStairs);
    stairs->addExit(stairsToPortal);
    portalRoom->addExit(portalToStairs);
    castleEntrance->addExit(entranceToCastle);
    library->addExit(libraryToHallway);
    stairs->addExit(stairsToLibrary);
    alterRoom->addExit(roomToAlter);
    alter->addExit(backFromAlter);


    Weapon* dagger = new Weapon("Mysterious Dagger", "A Mysterious Dagger lies on the ground in front of you", 15, "dagger.png");
    Key* key = new Key("Rustic Key", "An antique looking key", "key.png");
    Key* key2 = new Key("Rustic Key", "An antique looking key", "key.png");
    Potion* healingPotion = new Potion("Purple Potion", "A glistening purple potion",  10, "healingpotion.png", HEALING);
    Potion* damagePotion = new Potion("Green Potion", "An ominous potion", 25, "deathpotion.png", DAMAGING);

    bridgeEntrance->addItem(dagger);
    forestEntrance->addItem(key);
    catacombExit->addItem(damagePotion);
    bedroom->addItem(healingPotion);


    inventory.addItem(dagger);

    Interactable* alterSpell = new Interactable("Use Alter", "Use the alter to perform a cloning spell");
    alter->setInteractable(alterSpell);
    setCurrentRoom(bridgeEntrance);

    emit inventoryChanged();
}

