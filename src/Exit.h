#pragma once
#include "Entity.h"

// forward declaration of Room class
class Room;

class Exit: public Entity
{
public:
    Exit(string name, string description, Room* origin, Room* destination, bool locked);
    ~Exit();
    Room* getOrigin();
    Room* getDestination();
    bool locked;

private:
    Room* origin;
    Room* destination;
};