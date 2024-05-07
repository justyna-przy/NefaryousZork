#include "src/Exit.h"
#include "src/Room.h"

Exit::Exit(std::string name, std::string description, Room *origin, Room *destination, bool locked) :
    Entity(name, description),
    origin(origin), destination(destination)
{
    type = EXIT;
}

Exit::~Exit()
{
}

Room* Exit ::getOrigin() {
    return origin;
}

Room* Exit::getDestination() {
    return destination;
}

