#pragma once
#include <string>

using namespace std;

enum EntityType {
    ENTITY,
    EXIT,
    ITEM,
    ROOM,
};


class Entity
{
public:
    Entity(string name, string description);
    virtual ~Entity();

    string getName() const { return name; }
    string getDescription() const { return description; }
    EntityType type;

// faster option that the getter methods for accessing fields within subclasses
protected:
    string name;
    string description;
};