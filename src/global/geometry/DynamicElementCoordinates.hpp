#ifndef DYNAMICELEMENTCOORDINATES_HPP
#define DYNAMICELEMENTCOORDINATES_HPP

#include <QtCore/QtGlobal>

class TileCoordinates;

/**
 * @brief The coordinates of a dynamic element on the map.
 */
class DynamicElementCoordinates
{
    public:
        DynamicElementCoordinates(qreal x, qreal y);
        bool operator ==(const DynamicElementCoordinates& other) const;

        qreal x() const;
        qreal y() const;

        TileCoordinates associatedTileCoordinates() const;

    private:
        qreal _x;
        qreal _y;
};

#endif // DYNAMICELEMENTCOORDINATES_HPP
