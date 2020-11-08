#include "Direction.hpp"

#include <QtCore/QString>

#include "src/exceptions/BadConfigurationException.hpp"



uint qHash(const Direction& direction)
{
    return static_cast<uint>(direction);
}



Direction resolveDirection(const QString& direction)
{
    if (direction == "top")    return Direction::Top;
    if (direction == "right")  return Direction::Right;
    if (direction == "bottom") return Direction::Bottom;
    if (direction == "left")   return Direction::Left;
    if (direction == "north")  return Direction::North;
    if (direction == "east")   return Direction::East;
    if (direction == "south")  return Direction::South;
    if (direction == "west")   return Direction::West;

    throw BadConfigurationException("Unknown building of type \"" + direction + "\".");
}
