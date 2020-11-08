#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <QtCore/QtGlobal>

/**
 * An enumeration for available directions.
 */
enum class Direction {
    Top,
    Right,
    Bottom,
    Left,
    North,
    East,
    South,
    West
};

uint qHash(const Direction& direction);

Direction resolveDirection(const QString& direction);

#endif // DIRECTION_HPP
