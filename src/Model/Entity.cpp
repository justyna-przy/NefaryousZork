
#include "Entity.h"

// Constructor using initializer list
Entity::Entity(string name, string description) :
        name(name), description(description), type(ENTITY)
{
}

// De-constructor
Entity::~Entity()
{
}
