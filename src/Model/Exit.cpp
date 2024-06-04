#include <QtGui>
#include "Exit.h"
#include "Room.h"


Exit::Exit(std::string name, std::string description, Room *origin, Room *destination, bool locked) :
    Entity(name, description),
    origin(origin), destination(destination)
{
    type = EXIT;
}

Exit::~Exit()
{
}



